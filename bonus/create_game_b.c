#include "cub3d_b.h"

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

void	init_animation(t_game *game)
{
	int		i;

	game->anim->i = 0;
	game->anim->time = get_time();
	game->anim->tx[0] = mlx_load_png("assets/animation1/1.png");
	game->anim->tx[1] = mlx_load_png("assets/animation1/2.png");
	game->anim->tx[2] = mlx_load_png("assets/animation1/3.png");
	game->anim->tx[3] = mlx_load_png("assets/animation1/4.png");
	game->anim->tx[4] = mlx_load_png("assets/animation1/5.png");
	game->anim->tx[5] = mlx_load_png("assets/animation1/6.png");
	game->anim->tx[6] = mlx_load_png("assets/animation1/7.png");
	game->anim->tx[7] = mlx_load_png("assets/animation1/8.png");
	game->anim->tx[8] = mlx_load_png("assets/animation1/9.png");
	game->anim->tx[9] = mlx_load_png("assets/animation1/10.png");
	i = -1;
	while (++i < FRAMES)
	{
		if (game->anim->tx[i] == NULL)
			{
				fprintf(stderr, "Error: Failed to load texture at index %d\n", i);
				exit(EXIT_FAILURE); // Exit if any texture fails to load
			}
	}
	i = -1;
	
	while (++i < FRAMES)
	{
		game->anim->img[i] = mlx_texture_to_image(game->win, game->anim->tx[i]);
		game->anim->img[i]->enabled = (i == 0); // Only enable the first frame initially
		mlx_resize_image(game->anim->img[i], WIDTH, HEIGHT);
		mlx_image_to_window(game->win, game->anim->img[i], 0, 0);
	}
}

void	animation(t_game *game)
{
    if (get_time() - game->anim->time >= ANIMATION_DELAY)
	{
        game->anim->time = get_time();
        game->anim->img[game->anim->i % 10]->enabled = true;
		if (game->anim->i % 10 != 0)
        	game->anim->img[game->anim->i % 10 - 1]->enabled = false;
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
}