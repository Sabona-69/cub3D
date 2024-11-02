#include "cub3d_b.h"

void	my_pixel_put(mlx_image_t *img, uint32_t x, uint32_t y, uint32_t color)
{
	if (x < 0)
		return ;
	else if (x >= img->width)
		return ;
	if (y < 0)
		return ;
	else if (y >= img->height)
		return ;
	mlx_put_pixel(img, x, y, color);
}

void handle_key(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = param;
	if (keydata.key == MLX_KEY_ESCAPE && (keydata.action == MLX_PRESS))
		exit(0);
	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS))
		game->player->walk = LEFT;
	else if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS))
		game->player->walk = RIGHT;
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS))
		game->player->walk = DOWN;
	else if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		game->player->walk = UP;
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		game->player->turn = TURN_LEFT;
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		game->player->turn = TURN_RIGHT;
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_RELEASE))
		game->player->walk = STOP;
	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_RELEASE))
		game->player->walk = STOP;
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_RELEASE))
		game->player->walk = STOP;
	else if (keydata.key == MLX_KEY_W && (keydata.action == MLX_RELEASE))
		game->player->walk = STOP;
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_RELEASE)
		game->player->turn = STOP;
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_RELEASE)
		game->player->turn = STOP;
}

void	adjust_step(t_game *game, t_pos_d *delta, int is_vertical)
{
	if (is_vertical)
	{
		if (game->rays->left)
			delta->x *= -1;
		if (game->rays->up && delta->y > 0)
			delta->y *= -1;
		if (game->rays->down && delta->y < 0)
			delta->y *= -1;
	}
	else
	{
		if (game->rays->up)
			delta->y *= -1;
		if (game->rays->left && delta->x > 0)
			delta->x *= -1;
		if (game->rays->right && delta->x < 0)
			delta->x *= -1;
	}
}

void	check_input(int ac, char **av)
{
	if (ac != 2 || ft_strlen(av[1]) < 4
		| ft_strcmp(".cub", av[1] + ft_strlen(av[1]) - 4) != 0)
	{
		ft_putstr_fd(RED"Error\n"RESET, 2);
		exit(1);
	}
}

void    *ft_malloc(size_t size)
{
    void    *new;

    new = malloc(size);
    if (!new)
        (ft_putstr_fd("malloc failed !", 2), exit(1));
    ft_bzero(new, size);
    return(new);
}

void    allocate_t_game(t_game **game)
{
    (*game) = ft_malloc(sizeof(t_game));
    (*game)->data = ft_malloc(sizeof(t_data));
    (*game)->rays = ft_malloc(sizeof(t_ray));
    (*game)->player = ft_malloc(sizeof(t_pl));
    (*game)->anim= ft_malloc(sizeof(t_anim));
    (*game)->tx = ft_malloc(sizeof(t_tx));
}

int    main(int ac, char **av)
{
    t_game    *game;

    check_input(ac, av);
    allocate_t_game(&game);
    parse_it(av[1], game->data);
    create_game(game);
    exiting(game->data, 0);
}