#include "main.h"
/**
 * main - UNIX command line interpreter
 * Return: 0.
 */
int main(void)
{
	char *line;
	size_t size;
	int n_read = 0;
	int count = 0;
	char **words = NULL;
	pid_t pid;
	int status;
	const char *delim = " ";

	line = (char *)malloc(sizeof(char));
	size = (size_t)malloc(sizeof(size_t));
	if (line == NULL)
		exit(EXIT_FAILURE);
	while (1)
	{
		printf("#cisfun$");
		n_read = getline(&line, &size, stdin);
		line[n_read - 1] = '\0';
		words = tokenize(line, delim, &count);
		pid = fork();
		if (pid == -1)
		{
			perror("Error");
			free(line);
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			if (execve(words[0], &words[0], NULL) == -1)
			{
				perror("Error");
				free(line);
				exit(EXIT_FAILURE);
			}
		}
		else
			wait(&status);
	}
	free(line);
	return (0);
}
/**
 * tokenize - splits a string and returns an array of each
 * token/word of the string
 * @text: string to tokenize
 * @delim: delimiter(s) - can handle multiple delimiters
 * @count: buffer to hold number of tokens returned by
 * function
 * Return:  array of strings/tokens. Free allocated memory after use!
 */
char **tokenize(char *text, const char *delim, int *count)
{
	char **words;
	int i;
	int j;
	int count_delim = 1;
	/*Estimate the number of tokens in view*/
	i = 0;
	while (text[i])
	{
		for (j = 0; delim[j] != '\0'; j++)
		{
			if (text[i] == delim[j])
				count_delim++;
		}
		i++;
	}
	/*Allocate memory based on tokens in view*/
	words = malloc(sizeof(char *) * count_delim);
	/*Verify malloc was successful*/
	if (words == NULL)
	{
		printf("Malloc Failed!\n");
		exit(99);
	}
	/*Tokenize string and store in reserved array*/
	words[0] = strtok(text, delim);
	for (i = 1; i < count_delim; i++)
	{
		words[i] = strtok(NULL, delim);
	}
	/*Count tokens stored*/
	i = 0;
	count_delim = 0;
	while (words[i] != NULL)
	{
		count_delim++;
		i++;
	}
	/*Return every update*/
	*count = count_delim - 1;
	return (words);
}
