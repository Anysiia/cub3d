int		ft_strlen(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int		len_first_end_one(char *str)
{
	int		i;

	i = ft_strlen(str) - 1;
	while (i > 0 && str[i] == '1')
		i--;
	if (str[i] != '1')
		i += 1;
	i += 1;
	return (i);
}

#include <stdio.h>
int main(int ac, char **av)
{
	if (ac == 2)
	printf("%d\n", len_first_end_one(av[1]));
	return (0);
}
