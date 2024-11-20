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

long	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

mlx_image_t	**generating_frames(t_game *game, char *path, int frames)
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

void	animation(t_game *game)
{
	int	current_frame;
	int	previous_frame;

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
