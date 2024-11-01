#include "cub3d.h"

mlx_texture_t	*get_texture(t_game *game)
{
	if (game->rays->was_hit_vertical)
	{
		if (game->rays->angl > M_PI / 2 && game->rays->angl < 3 * (M_PI / 2))
			return (game->tx->e);
		else
			return (game->tx->w);
	}
	else
	{
		if (game->rays->angl > 0 && game->rays->angl < M_PI)
			return (game->tx->n);
		else
			return (game->tx->s);
	}
}

int	get_texture_x(mlx_texture_t *texture, t_game *game)
{
	double	offset_x;

	if (game->rays->was_hit_vertical)
		offset_x = fmod(game->rays->v_wall.y, TILE_SIZE);
	else
		offset_x = fmod(game->rays->h_wall.x, TILE_SIZE);
	offset_x = (offset_x * texture->width) / TILE_SIZE;
	return (offset_x);
}

int	get_texture_y(mlx_texture_t *texture, t_game *game, int y, int wall_h)
{
	double	step;
	double	offset_y;
	int		wall_t;

	wall_t = (game->win->height / 2) - (wall_h / 2);
	step = (double)texture->height / wall_h;
	offset_y = ((y - wall_t) * step);
	if (offset_y >= texture->height)
		offset_y = texture->height - 1;
	if (offset_y < 0)
		offset_y = 0;
	return (offset_y);
}

static void	draw_ceiling(t_game *game, int wall_t)
{
	int		i;
	int		color;

	color = ft_get_color(game->data->C[0], game->data->C[1],game->data->C[2], 255);
	i = 0;
	while (i < wall_t)
		my_pixel_put(game->img, game->rays->index, i++, color);
}

static void	draw_wall(t_game *game, int wall_t, int wall_b, double wall_h)
{
	t_pos		offset;
	mlx_texture_t	*texture;
	uint32_t		*arr;
	uint32_t		color;
	int				y;

	// load_textures(game);
	texture = get_texture(game);
	arr = (uint32_t *)texture->pixels;
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
	color = ft_get_color(game->data->F[0], game->data->F[1], game->data->F[2], 255);
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