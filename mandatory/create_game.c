#include "../include/cub3d.h"

void	load_textures(t_game *game)
{
	game->tx->e = mlx_load_png(game->data->ea);
	game->tx->w = mlx_load_png(game->data->we);
	game->tx->s = mlx_load_png(game->data->so);
	game->tx->n = mlx_load_png(game->data->no);
	if (!game->tx->e || !game->tx->w || !game->tx->s || !game->tx->n)
		exiting(game, "Invalid texture");
}

void	update(void *p)
{
	t_game	*game;

	game = p;
	// ft_clear_img(game->img);
	movement(game, 0, 0);
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

void	create_game(t_game *game)
{
	if (WIDTH < 0 || WIDTH > 2560 || HEIGHT < 0 || HEIGHT > 1440)
		exiting(game, "Invalid resolution");
	game->win = mlx_init(WIDTH, HEIGHT, "cub3D", true);
	if (!game->win)
		exiting(game, "mlx failed");
	game->img = mlx_new_image(game->win, WIDTH, HEIGHT);
	if (!game->img)
		exiting(game, "mlx img failed");
	mlx_image_to_window(game->win, game->img, 0, 0);
	load_textures(game);
	set_player(game);
	mlx_loop_hook(game->win, &update, game);
	mlx_key_hook(game->win, &handle_key, game);
	mlx_loop(game->win);
}
