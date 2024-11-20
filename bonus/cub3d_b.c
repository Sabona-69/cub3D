#include "../include/cub3d_b.h"

void	exiting(t_game *game, char *message, int status)
{
	int		i;

	i = -1;
	(free(game->data->ea), free(game->data->we), free(game->data->so));
	free(game->data->no);
	if (game->data->map)
		free2d(game->data->map, ft_strlen2d(game->data->map));
	(free(game->data->line), close(game->data->fd));
	if (status == GAME)
	{
		mlx_close_window(game->win);
		mlx_delete_image(game->win, game->img);
		while (++i < FRAMES)
			if (game->anim->img[i])
				mlx_delete_image(game->win, game->anim->img[i]);
		(free(game->anim->img), free(game->anim));
		mlx_delete_texture(game->tx->e);
		mlx_delete_texture(game->tx->w);
		(mlx_delete_texture(game->tx->s), mlx_delete_texture(game->tx->n));
		(free(game->tx), free(game->rays), free(game->player));
		(free(game->data), free(game));
	}
	if (message)
		(printf(RED"%s !\n" RESET, message), exit(1));
	exit(0);
}

void	check_input(int ac, char **av)
{
	if (ac != 2 || ft_strlen(av[1]) < 4
		|| ft_strcmp(".cub", av[1] + ft_strlen(av[1]) - 4) != 0)
	{
		ft_putstr_fd(RED"Error\n"RESET, 2);
		exit(1);
	}
}

void	allocate_t_game(t_game **game)
{
	(*game) = ft_malloc(sizeof(t_game));
	(*game)->data = ft_malloc(sizeof(t_data));
	(*game)->rays = ft_malloc(sizeof(t_ray));
	(*game)->player = ft_malloc(sizeof(t_pl));
	(*game)->anim = ft_malloc(sizeof(t_anim));
	(*game)->tx = ft_malloc(sizeof(t_tx));
}

void f(){
	system("leaks cub3D_bonus");
}

int	main(int ac, char **av)
{
	t_game	*game;

	atexit(f);
	check_input(ac, av);
	allocate_t_game(&game);
	parse_it(av[1], game);
	create_game(game);
}
