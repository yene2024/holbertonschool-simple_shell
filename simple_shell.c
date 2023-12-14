#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024

void display_prompt()
{
	printf("#cisfun$ ");
	fflush(stdout);
}

int main()
{
	char input[MAX_INPUT_SIZE];

	while (1)
	{
		display_prompt();

		if (fgets(input, sizeof(input), stdin) == NULL)
		{
			printf("\n");
			break;
		}

		size_t input_length = strlen(input);
		if (input_length > 0 && input[input_length - 1] == '\n')
		{
			input[input_length - 1] = '\0';
		}

		pid_t pid = fork();

		if (pid == -1)
		{
			perror("Fork error");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			if (execve(input, (char *const [])
						{input, NULL}, NULL) == -1)
			{
				perror("Command not found");
				exit(EXIT_FAILURE);
			}
			exit(EXIT_SUCCESS);
        }
		else
		{
			waitpid(pid, NULL, 0);
		}
	}

	return 0;
}

