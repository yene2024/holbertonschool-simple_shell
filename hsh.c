#include "shell.h"
#include "simple_shell.c"
/**
 * main - Entry point for the simple shell program
 * @argc: The argument count (unused)
 * @argv: The argument vector (unused)
 * @envp: The environment variables
 * Return: Always 0
 */
int main(int argc __attribute__((unused)), char **argv, char **envp)
{
	char *user_input = NULL;
	size_t input_size = 0;
	ssize_t read_size;
	char *trimmed_input;

	while (1)
	{
		if (isatty(0))
			write(STDOUT_FILENO, "$ ", 2);
		(void)argv; /* Suppress unused parameter warning */
		read_size = getline(&user_input, &input_size, stdin); /* Read user input */
		if (read_size == -1)
			break;
		/* Trim leading and trailing whitespace */
		trimmed_input = trim(user_input);
		if (strcmp(trimmed_input, "exit") == 0)
			break;
		if (trimmed_input[0] == '\0')
			continue;
		Tok(trimmed_input, envp); /* Execute the command entered by the user */
	}
	free(user_input); /* Free allocated memory */
	return (0);	     /* Exit the shell */
}

/**
 * trim - Remove leading and trailing whitespace from a string
 * @str: The string to trim
 * Return: A pointer to the trimmed string
 */
char *trim(char *str)
{
	char *end = str + strlen(str) - 1; /* Pointer to the end of the string */

	/* Remove leading whitespace */
	while (isspace((unsigned char)(*str)))
		str++;

	/* Remove trailing whitespace */
	while (end > str && isspace((unsigned char)*end))
		end--;

	/* Null-terminate the trimmed string */
	*(end + 1) = '\0';

	return (str); /* Return the trimmed string */
}

/**
 * free_token - Frees memory allocated for token array and token strings
 * @tokens: The token array to be freed
 * @token_count: The number of tokens in the array
 */
void free_token(char **tokens, int token_count)
{
	int i;

	for (i = 0; i < token_count; i++)
	{
		free(tokens[i]);
	}
	free(tokens);
}

/**
 * free_paths_array - Frees memory allocated for the paths array
 * @paths: The paths array to be freed
 * @num_paths: The number of paths in the array
 */
void free_paths_array(char **paths, int num_paths)
{
	int i;

	for (i = 0; i < num_paths; i++)
	{
		free(paths[i]);
	}
	free(paths);
}

