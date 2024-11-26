#include "../include/cub3d_b.h"

static void	draw_ceiling(t_game *game, int wall_t)
{
	int		i;
	int		color;

	color = ft_get_color(game->data->c[0], game->data->c[1],
			game->data->c[2], 255);
	i = 0;
	while (i < wall_t)
		my_pixel_put(game->img, game->rays->index, i++, color);
}

static void	draw_wall(t_game *game, int wall_t, int wall_b, double wall_h)
{
	mlx_texture_t	*texture;
	t_pos			offset;
	int				*arr;
	int				color;
	int				y;

	texture = get_texture(game);
	arr = (int *)texture->pixels;
	offset.x = get_texture_x(texture, game);
	if (game->tx->w == texture || game->tx->s == texture)
		offset.x = texture->width - offset.x - 1;
	y = wall_t;
	while (y < wall_b)
	{
		offset.y = get_texture_y(texture, game, y, wall_h);
		color = reverse_bytes(arr[offset.y * texture->width + offset.x]);
		my_pixel_put(game->img, game->rays->index, y, color);
		y++;
	}
}

static void	draw_floor(t_game *game, int wall_b)
{
	int		color;

	color = ft_get_color(game->data->f[0], game->data->f[1],
			game->data->f[2], 255);
	while (wall_b < game->win->height)
		my_pixel_put(game->img, game->rays->index, wall_b++, color);
}

void	projected_wall(t_game *game)
{
	double	wall_h;
	double	disproplan;
	int		wall_t;
	int		wall_b;

	game->rays->distance *= cos(game->rays->angl - game->player->direction);
	disproplan = (game->win->width / 2) / tan(game->player->view / 2);
	wall_h = (TILE_SIZE / game->rays->distance) * disproplan;
	wall_b = (game->win->height / 2) + (wall_h / 2);
	wall_t = (game->win->height / 2) - (wall_h / 2);
	if (wall_b > game->win->height)
		wall_b = game->win->height;
	if (wall_t < 0)
		wall_t = 0;
	draw_ceiling(game, wall_t);
	draw_wall(game, wall_t, wall_b, wall_h);
	draw_floor(game, wall_b);
}
