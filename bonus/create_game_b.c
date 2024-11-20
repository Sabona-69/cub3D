#include "../include/cub3d_b.h"

void	load_textures(t_game *game)
{
	game->tx->e = mlx_load_png(game->data->ea);
	game->tx->w = mlx_load_png(game->data->we);
	game->tx->s = mlx_load_png(game->data->so);
	game->tx->n = mlx_load_png(game->data->no);
}

void	update(void *p)
{
	t_game	*game;

	game = p;
	ft_clear_img(game->img);
	movement(game, 0, 0);
	animation(game);
	raycasting(game);
}

void	set_player(t_game *game)
{
	char	c;

	c = game->data->player_facing;
	if (c == 'E')
		game->player->direction = 0;
	else if (c == 'N')
		game->player->direction = (3 * M_PI) / 2;
	else if (c == 'W')
		game->player->direction = M_PI;
	else if (c == 'S')
		game->player->direction = M_PI / 2;
	game->player->start.x = (game->data->player_postion.x * TILE_SIZE)
		+ TILE_SIZE / 2;
	game->player->start.y = (game->data->player_postion.y * TILE_SIZE)
		+ TILE_SIZE / 2;
	game->player->view = FOV * (M_PI / 180);
	game->player->walk = STOP;
	game->player->turn = STOP;
}

void	handle_mouse(void *param)
{
	t_game	*game;
	int		mouse_x;
	int		mouse_y;
	int		dx;

	game = param;
	if (!game->mouse_on)
		return ;
	mlx_get_mouse_pos(game->win, &mouse_x, &mouse_y);
	dx = mouse_x - game->data->height / 2;
	game->player->direction += dx * 0.001;
	game->player->direction = normalize_angle(game->player->direction);
	mlx_set_mouse_pos(game->win, game->data->width / 2, \
			game->data->height / 2);
}

void	create_game(t_game *game)
{
	game->win = mlx_init(WIDTH, HEIGHT, "cub3D", true);
	game->img = mlx_new_image(game->win, WIDTH, HEIGHT);
	mlx_image_to_window(game->win, game->img, 0, 0);
	load_textures(game);
	init_animation(game);
	set_player(game);
	mlx_loop_hook(game->win, &update, game);
	mlx_key_hook(game->win, &handle_key, game);
	mlx_cursor_hook(game->win, (void *)handle_mouse, game);
	mlx_loop(game->win);
}
