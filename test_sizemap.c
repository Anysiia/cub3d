/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_sizemap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 12:19:29 by cmorel-a          #+#    #+#             */
/*   Updated: 2020/01/23 12:25:50 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
void		size_map(char *map)
{
	int		i;
	int		height;
	int		width;
	int		max_width;

	i = 0;
	height = 0;
	width = 0;
	max_width = 0;
	while (map[i++])
	{
		if (map[i] == '\n')
		{
			height++;
			if (max_width < width)
				max_width = width;
			width = -1;
		}
		width++;
	}
	printf("%d-%d\n", height, max_width);
}

int main()
{
	size_map("111\n11111\n1222\n");
	size_map("");
	size_map("111111111111\n11111\n1222\n111\n55\n99\n789\n");
	size_map("111111111111\n11111\n1222\n111\n55\n99\n789\n");
}
