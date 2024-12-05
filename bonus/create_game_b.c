#include "../include/cub3d_b.h"

static void	load_textures(t_game *game)
{
	game->tx->e = mlx_load_png(game->data->ea);
	game->tx->w = mlx_load_png(game->data->we);
	game->tx->s = mlx_load_png(game->data->so);
	game->tx->n = mlx_load_png(game->data->no);
	game->tx->door = mlx_load_png("assets/door.png");
	if (!game->tx->e || !game->tx->w || !game->tx->s
		|| !game->tx->n || !game->tx->door)
		exiting(game, "Invalid texture");
}

static void	update(void *p)
{
	t_game	*game;

	game = p;
	movement(game, 0, 0);
	animation(game);
	raycasting(game);
	draw_minimap(game);
}

static void	set_player(t_game *game)
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

static void	handle_mouse(void *param)
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
	if (WIDTH < 0 || WIDTH > 2560 || HEIGHT < 0 || HEIGHT > 1440)
		exiting(game, "Invalid resolution");
	game->win = mlx_init(WIDTH, HEIGHT, "cub3D_bonus", true);
	if (!game->win)
		exiting(game, "mlx failed");
	game->img = mlx_new_image(game->win, WIDTH, HEIGHT);
	if (!game->img)
		exiting(game, "mlx img failed");
	if (mlx_image_to_window(game->win, game->img, 0, 0) == -1)
		exiting(game, "mlx img to window failed");
	load_textures(game);
	init_animation(game);
	set_player(game);
	game->pid = fork();
	if (game->pid == 0)
		play_sound(OPENING);
	if (game->pid != 0)
	{
		mlx_loop_hook(game->win, update, game);
		mlx_key_hook(game->win, handle_key, game);
		mlx_cursor_hook(game->win, (void *)handle_mouse, game);
		mlx_loop(game->win);
	}
}
