#include <stdio.h>

int		check_flag(char *argv)
{
	int j;

	j = 1;
	while (argv[j])
	{
		if (argv[j] == 'n')
			j++;
		else
			return (0);
	}
	return (1);
}

void	m_echo(int argc, char **argv)
{
	int i;
	int j;
	int flag;
	
	i = 0;
	j = 0;
	flag = 0;
	while (argv[++i][j] == '-')
	{
		if (check_flag(argv[i]) == 1)
			flag = 1;
		else
		{
			i--;
			break;
		}
	}
	while (i < argc)
	{
		printf("%s", argv[i]);
		i++;
		if (argv[i])
			printf(" ");
	}
	if (flag == 0)
		printf("\n");
}

int main(int argc, char **argv)
{
	m_echo(argc - 1, argv + 1);
	return (0);
}