#include "../include/cub3d.h"

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
	int				i;

	i = 0;
	new = ft_malloc(frames * sizeof(mlx_image_t *), MALLOC);
	if (!new)
		return (NULL);
	while (i < frames)
	{
		tx = mlx_load_png(ft_strjoin(ft_strjoin(path, ft_itoa(i + 1)), ".png"));
		if (!tx)
			exiting(game, "Invalid texture");
		new[i] = mlx_texture_to_image(game->win, tx);
		new[i]->enabled = (i == 0);
		mlx_resize_image(new[i], WIDTH, HEIGHT);
		mlx_image_to_window(game->win, new[i], 0, 0);
		mlx_delete_texture(tx);
		i++;
	}
	return (new);
}