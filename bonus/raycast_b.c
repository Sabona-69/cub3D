#include "../include/cub3d_b.h"

static void	check_rayfacing(t_game *game, double angle)
{
	game->rays->down = angle > 0 && angle < M_PI;
	game->rays->up = !game->rays->down;
	game->rays->right = angle < (M_PI / 2) || angle > (3 * M_PI / 2);
	game->rays->left = !game->rays->right;
}

static double	horizontal_intersect(t_game *game)
{
	t_pos_d	inter;
	t_pos_d	delta;

	inter.y = floor(game->player->start.y / TILE_SIZE) * TILE_SIZE;
	if (game->rays->down)
		inter.y += TILE_SIZE;
	inter.x = game->player->start.x
		+ (inter.y - game->player->start.y) / tan(game->rays->angl);
	delta.y = TILE_SIZE;
	delta.x = TILE_SIZE / tan(game->rays->angl);
	adjust_step(game, &delta, 0);
	while (!is_wall(inter.x, inter.y - game->rays->up, game))
	{
		inter.x += delta.x;
		inter.y += delta.y;
	}
	game->rays->h_wall = inter.x;
	game->door->h_door = game->door->hit_door;
	return (calcul_distance(inter, game->player->start));
}

static double	vertical_intersect(t_game *game)
{
	t_pos_d	inter;
	t_pos_d	delta;

	inter.x = floor(game->player->start.x / TILE_SIZE) * TILE_SIZE;
	if (game->rays->right)
		inter.x += TILE_SIZE;
	inter.y = game->player->start.y
		+ (inter.x - game->player->start.x) * tan(game->rays->angl);
	delta.x = TILE_SIZE;
	delta.y = TILE_SIZE * tan(game->rays->angl);
	adjust_step(game, &delta, 1);
	while (!is_wall(inter.x - game->rays->left, inter.y, game))
	{
		inter.x += delta.x;
		inter.y += delta.y;
	}
	game->rays->v_wall = inter.y;
	game->door->v_door = game->door->hit_door;
	return (calcul_distance(inter, game->player->start));
}

void	raycasting(t_game *game)
{
	t_pos_d	dis;

	game->rays->index = -1;
	game->rays->angl = game->player->direction - (game->player->view / 2);
	while (++game->rays->index < game->win->width)
	{
		game->rays->angl = normalize_angle(game->rays->angl);
		check_rayfacing(game, game->rays->angl);
		dis.y = vertical_intersect(game);
		dis.x = horizontal_intersect(game);
		if (dis.y <= dis.x)
		{
			game->rays->distance = dis.y;
			game->rays->was_hit_vertical = 1;
			game->door->hit_door = game->door->v_door;
		}
		else
		{
			game->rays->distance = dis.x;
			game->rays->was_hit_vertical = 0;
			game->door->hit_door = game->door->h_door;
		}
		projected_wall(game);
		game->rays->angl += (game->player->view / game->win->width);
	}
}
