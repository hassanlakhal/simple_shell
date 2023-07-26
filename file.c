#include"main.h"
void parssing(char *str,char **env)
{
	int i = execve(str,NULL,env);
	if (i == -1)
		printf("./shell: No such file or directory\n");
	printf("%d\n",i);

}
int main(int argc , char **argv, char **env)
{
	while (1)
	{
		char *str = readline("sh: -> ");
		parssing(str,env);
		if (str == NULL)
		{
			free(str);
			exit(0);
		}
		free(str);
	}

}
