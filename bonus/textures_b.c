#include "../include/cub3d_b.h"

mlx_texture_t	*get_texture(t_game *game)
{
	if (game->door->hit_door)
		return (game->tx->door);
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
