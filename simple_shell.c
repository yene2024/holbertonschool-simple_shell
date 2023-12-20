#include "shell.h"
#include <stddef.h>
#include <stdio.h>

/**
 * get_path - Get the full path of a command
 * @com_name: The name of the command
 * Return: A dynamically allocated string containing the full path
 *         NULL if the command is not found
 */
char *get_path(char *com_name)
{
	char *com_path = "/bin/";
	char *conpath;

	if (access(com_name, X_OK) == 0)
	{
		conpath = strdup(com_name);
		if (conpath == NULL)
		{
			perror("malloc");
			return (NULL);
		}
		return (conpath);
	}
	conpath = malloc(strlen(com_path) + strlen(com_name) + 1);
	if (conpath == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	sprintf(conpath, "%s%s", com_path, com_name);
	if (access(conpath, X_OK) != 0)
	{
		free(conpath);
		return (NULL);
	}
	/*perror("Command not found");*/
	/*free(conpath);*/
	return (conpath);
}


/**
 * Tok - Tokenize a command string and execute it
 * @tokI: The command string to tokenize
 * @env: The environment variables
 */
void Tok(char *tokI, char **env)
{
	char *tok = NULL;
	char **tokens = NULL;
	int counter = 0;
	char *all_path;

	tok = strtok(tokI, " \n"); /* Tokenize the command string */
	if (tok == NULL)
		return;

	while (tok != NULL)
	{
		tokens = realloc(tokens, sizeof(char *) * (counter + 1));
		if (tokens == NULL)
		{
			perror("realloc");
			return;
		}
		tokens[counter] = strdup(tok); /* Store token in tokens array */
		counter++;					   /* Increment the token count */
		tok = strtok(NULL, " \n");	   /* Get next token from command string */
	}
	tokens = realloc(tokens, sizeof(char *) * (counter + 1));
	if (tokens == NULL)
	{
		perror("realloc");
		return;
	}
	tokens[counter] = NULL; /* Set next element in the array to NULL */
	all_path = get_path(tokens[0]); /* Get the full path of the command */
	if (all_path == NULL)
	{
		fprintf(stderr, "Command not found: %s\n", tokens[0]);
		free_token(tokens, counter);
		return;
	}
	free(tokens[0]);
	tokens[0] = all_path;
	child_creator(tokens, env);
	free_token(tokens, counter);
}

/**
 * child_creator - Create a child process and execute the command
 * @tokens: The tokenized command and arguments
 * @env: The environment variables
 */
void child_creator(char **tokens, char **env)
{
	pid_t pid = fork(); /* Create a child process */
	int status;

	if (pid == -1)
	{
		perror("fork"); /* Print error message if fork fails */
		return;
	}
	if (pid == 0)
	{
		execve(tokens[0], tokens, env); /* Execute the command using execve */
		perror("error ");				/* Print an error message if execve fails */
		exit(EXIT_FAILURE);				/* Exit child process with failure status */
	}
	else
	{
		/* Wait specifically for the child process to complete */
		waitpid(pid, &status, 0);
	}
}
