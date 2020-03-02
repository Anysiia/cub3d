#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>


size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int		ft_test_set(const char c, const char *charset)
{
	int		i;

	i = 0;
	while (charset[i])
	{
		if (charset[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	exit_error(const char *msg)
{
	if (msg)
		write(1, msg, ft_strlen(msg));
	write(1, "\n", 1);
	exit(0);
}

char	*clean_string(char *line)
{
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = ft_strlen(line);
	while (i < len)
	{
		if (!(ft_test_set(line[i], " NSEW012")))
			exit_error("Error:\nInvalid character on map");
		if (line[i + 1] != ' ' && line[i + 1] != '\0')
			exit_error("Error:\nElement of map must be separated by one space");
		line[j] = line[i];
		i += 2;
		j++;
	}
	line[j] = '\0';
	return (line);
}

int main(int ac, char **av)
{
	char	*s;

	if (ac == 2)
		printf("%s\n", clean_string(av[1]));
	return (0);
}
