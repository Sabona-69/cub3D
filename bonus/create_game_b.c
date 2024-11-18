#include "../include/cub3d_b.h"

void	ft_clear_img(mlx_image_t *img)
{
	u_int32_t	i;
	u_int16_t	j;

	i = 0;
	while (i < img->height)
	{
		j = 0;
		while (j < img->width)
		{
			mlx_put_pixel(img, j, i, 0);
			j++;
		}
		i++;
	}
}

void	load_textures(t_game *game)
{
	game->tx->e = mlx_load_png(game->data->ea);
	game->tx->w = mlx_load_png(game->data->we);
	game->tx->s = mlx_load_png(game->data->so);
	game->tx->n = mlx_load_png(game->data->no);
}

long	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

mlx_image_t		**generating_frames(t_game *game, char *path, int frames)
{
	mlx_image_t		**new;
	mlx_texture_t	*tx;
	char			*tmp;
	char			*join;
	int				i;

	i = 0;
	new = ft_malloc(frames * sizeof(mlx_image_t *));
	while (i < frames)
	{
		tmp = ft_itoa(i + 1);
		join = ft_strjoin(path, tmp);
		free(tmp);
		tmp = ft_strjoin(join, ".png");
		tx = mlx_load_png(tmp);
		new[i] = mlx_texture_to_image(game->win, tx);
		new[i]->enabled = (i == 0);
		mlx_resize_image(new[i], WIDTH, HEIGHT);
		mlx_image_to_window(game->win, new[i], 0, 0);
		free(join);
		mlx_delete_texture(tx);
		// free(tx);
		free(tmp);
		i++;
	}
	return (new);
}

void	init_animation(t_game *game)
{
	game->anim->i = 0;
	game->anim->time = get_time();
	game->anim->img = generating_frames(game, "assets/animation/", FRAMES);
}

void animation(t_game *game)
{
	int current_frame;
	int previous_frame;

    if (get_time() - game->anim->time >= ANIMATION_DELAY)
	{
		game->anim->time = get_time();
		current_frame = game->anim->i % FRAMES;
		previous_frame = (current_frame - 1 + FRAMES) % FRAMES;
		game->anim->img[current_frame]->enabled = true;
		game->anim->img[previous_frame]->enabled = false;
		game->anim->i = (game->anim->i + 1) % FRAMES;
	}
}

void update(void *p)
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
	game->player->start.x = (game->data->player_postion.x * TILE_SIZE) + TILE_SIZE / 2;
	game->player->start.y = (game->data->player_postion.y * TILE_SIZE) + TILE_SIZE / 2;
	game->player->view = FOV * (M_PI / 180);
	game->player->walk = STOP;
	game->player->turn = STOP;
}

void 	func(void *data)
{
	t_game *game;
	// int		i;

	game = data;
	free(game->data->ea);
	free(game->data->we);
	free(game->data->so);
	free(game->data->no);
	if (game->data->map)
		free2d(game->data->map, ft_strlen2d(game->data->map));
	free(game->data->line);
	close(game->data->fd);
	// if (status == GAME)
	// {
	// 	mlx_close_window(game->win);
	// 	mlx_delete_image(game->win, game->img);
	// 	i = -1;
	// 	while (++i < FRAMES)
	// 		if (game->anim->img[i])
	// 			mlx_delete_image(game->win, game->anim->img[i]);
		free(game->anim->img);
		free(game->anim);
		mlx_delete_texture(game->tx->e);
		mlx_delete_texture(game->tx->w);
		mlx_delete_texture(game->tx->s);
		mlx_delete_texture(game->tx->n);
		free(game->tx);
		free(game->rays);
		free(game->player);
		free(game->data);
		free(game);
	// if (message)
	// 	(printf(RED"%s !\n" RESET, message), exit(1));
	exit(0);
}

void create_game(t_game *game)
{
	game->win = mlx_init(WIDTH, HEIGHT, "cub3D", true);
	game->img = mlx_new_image(game->win, WIDTH, HEIGHT);
	mlx_image_to_window(game->win, game->img, 0, 0);
	load_textures(game);
	init_animation(game);
	set_player(game);
	mlx_loop_hook(game->win, &update, game);
	mlx_key_hook(game->win, &handle_key, game);
	mlx_loop(game->win);
	printf ("here\n");
	mlx_close_hook(game->win, func, (void *)game);
}
