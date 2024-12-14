#include "../include/cub3d_b.h"

static void	draw_ceiling(t_game *game, int top_half)
{
	int		i;
	int		color;

	color = ft_get_color(game->data->c[0], game->data->c[1],
			game->data->c[2], 255);
	i = 0;
	while (i < top_half)
		my_pixel_put(game->img, game->rays->index, i++, color);
}

static void	draw_wall(t_game *game, int top_half
, int bottom_half, double wall_height)
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
	y = top_half;
	while (y < bottom_half)
	{
		offset.y = get_texture_y(texture, game, y, wall_height);
		color = reverse_bytes(arr[offset.y * texture->width + offset.x]);
		my_pixel_put(game->img, game->rays->index, y, color);
		y++;
	}
}

static void	draw_floor(t_game *game, int bottom_half)
{
	int		color;

	color = ft_get_color(game->data->f[0], game->data->f[1],
			game->data->f[2], 255);
	while (bottom_half < game->win->height)
		my_pixel_put(game->img, game->rays->index, bottom_half++, color);
}

void	projected_wall(t_game *game)
{
	double	wall_height;
	double	new_projection;
	int		top_half;
	int		bottom_half;

	game->rays->distance *= cos(game->rays->angl - game->player->direction);
	new_projection = (game->win->width / 2) / tan(game->player->view / 2);
	wall_height = (TILE_SIZE / game->rays->distance) * new_projection;
	bottom_half = (game->win->height / 2) + (wall_height / 2);
	top_half = (game->win->height / 2) - (wall_height / 2);
	if (bottom_half > game->win->height)
		bottom_half = game->win->height;
	if (top_half < 0)
		top_half = 0;
	draw_ceiling(game, top_half);
	draw_wall(game, top_half, bottom_half, wall_height);
	draw_floor(game, bottom_half);
}
