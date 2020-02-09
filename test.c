#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mlx.h>

typedef struct	data_s
{
    void	*mlx_ptr;
    void	*mlx_win;
}				data_t;

void	rectangle(int x, int y, int pos_x, int pox_y, int color, data_t data)
{
	int		i;
	int		j;

	i = 0;
	while (i < x)
	{
		j = 0;
		while (j < y)
		{
			mlx_pixel_put(data.mlx_ptr, data.mlx_win, (i + pos_x), (j+ pox_y), color);
			j++;
		}
		i++;
	}
}

int		key_pressed(int key, data_t *data)
{
	if (key == 53)
	{
		mlx_destroy_window(data->mlx_ptr, data->mlx_win);
		exit(0);
	}
	return (1);
}


int main(void)
{
    data_t	data;

    if ((data.mlx_ptr = mlx_init()) == NULL)
        return (1);
    if ((data.mlx_win = mlx_new_window(data.mlx_ptr, 640, 480, "cub3d")) == NULL)
        return (1);
	rectangle(100, 100, 100, 100, 1546789, data);
	rectangle(200, 100, 450, 300, 325489, data);
	rectangle(50, 400, 200, 100, 9876789, data);
	rectangle(98, 25, 127, 20, 987789, data);
	rectangle(100, 100, 100, 100, 1546789, data);
	mlx_hook(data.mlx_win, 2, 1L << 0, key_pressed, &data);
	mlx_loop(data.mlx_ptr);
    return (0);
}
