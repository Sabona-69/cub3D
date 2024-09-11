#include "cub3d.h"

void	create_game(t_data *cub)
{
	// void *init = mlx_init();
	// void *window = mlx_new_window(init, 1080 * 64, 1920 * 64, "cub3d");
	// mlx_loop(init);
	// mlx_put_image_to_window(vrs->game.init, vrs->game.window,
	// 	s, x * 64, y * 64);
}

#include <string.h>

int main(int ac, char **av)
{
	t_data *cub;
	// atexit(f);
	if (ac != 2 || ft_strlen(av[1]) < 4 || ft_strcmp(".cub", av[1] + ft_strlen(av[1]) - 4) != 0)
		return (printf("Please Insert \"./cub\" + valid map\n"), 1);
	cub = malloc(sizeof(t_data));
	if (!cub)
		return (ft_putstr_fd("malloc failed ", 2), 1);
	ft_memset(cub, 0, sizeof(t_data));
	// (1) && (cub->C[0] = -1, cub->F[0] = -1);
	parse_it(av[1], cub);
	// create_game(cub);
	// raycasting();
	free_it(cub->map, ft_strlen2d(cub->map));
	// free(cub->EA);
	// free(cub->NO);
	// free(cub->SO);
	// free(cub->WE);
	// free(cub);
	// printf("%d\n", my_atoi(av[1]));
}