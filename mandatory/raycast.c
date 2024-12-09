#include "../include/cub3d.h"

static void    check_rayfacing(t_game *game, double angle)
{
    if (angle > 0 && angle < M_PI)
    {
        game->rays->down = 1;
        game->rays->up = 0;
    }
    else
    {
        game->rays->down = 0;
        game->rays->up = 1;
    }
    if (angle < M_PI / 2 || angle > 3 * M_PI / 2)
    {
        game->rays->right = 1;
        game->rays->left = 0;
    }
    else
    {
        game->rays->right = 0;
        game->rays->left = 1;
    }
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
	game->rays->h_wall.x = inter.x;
	game->rays->h_wall.y = inter.y;
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
	game->rays->v_wall.x = inter.x;
	game->rays->v_wall.y = inter.y;
	return (calcul_distance(inter, game->player->start));
}

void	raycasting(t_game *game)
{
	t_pos_d	distance;

	game->rays->index = 0;
	game->rays->angl = game->player->direction - (game->player->view / 2);
	while (game->rays->index < 3000)
	{ 
		fprintf(stderr, "%d\n", game->rays->index);
		game->rays->angl = normalize_angle(game->rays->angl);
		check_rayfacing(game, game->rays->angl);
		distance.y = vertical_intersect(game);
		distance.x = horizontal_intersect(game);
		if (distance.y <= distance.x)
		{
			game->rays->distance = distance.y;
			game->rays->was_hit_vertical = 1;
		}
		else
		{
			game->rays->distance = distance.x;
			game->rays->was_hit_vertical = 0;
		}
		projected_wall(game);
		game->rays->index++;
		game->rays->angl += (game->player->view / game->win->width);
	}
}
