int		ft_strlen(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int		len_to_no_one(char *str)
{
	int		i;

	i = ft_strlen(str);
	i--;
	while (str[i] == '1')
		i--;
	i++;
	return (i);
}

#include <stdio.h>
int main(int ac, char **av)
{
	if (ac == 2)
	printf("%d\n", len_to_no_one(av[1]));
	return (0);
}
