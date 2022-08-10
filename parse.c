#include "main.h"

/**
 * _parse - split environment variable
 * @ptrData: data structure
 *
 * Return: string array
 */
char **_parse(server_t *ptrData)
{
char **paths;
serverEnv_t *ptrNode;

ptrNode = _getenv(ptrData->env, "PATH");
paths = _strtow(ptrNode->value, ":", NULL);

return (paths);
}

/**
 * _genAbs - Generate an absolute path from environment variable
 *
 * @ptrPath: path environment variable
 * @ptrCmdName: command name
 *
 * Return: absolute path
 */
char *_genAbs(char *ptrPath, char *ptrCmdName)
{
	char *tmp, *path, *absolutePath, lastCharacter;
	int pathValueSize;

	path = _strdup(ptrPath);
	pathValueSize = _strlen(path);
	lastCharacter = path[pathValueSize - 1];

	if (lastCharacter != '/')
	{
		tmp = path;
		path = _strconcat(tmp, "/");
		free(tmp);
	}

	tmp = "";
	tmp = _strconcat(tmp, path);
	absolutePath = _strconcat(tmp, ptrCmdName);
	free(tmp);
	free(path);

	return (absolutePath);
}
