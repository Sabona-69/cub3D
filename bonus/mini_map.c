#include "../include/cub3d_b.h"

static void	draw_player_direction(t_game *game)
{
	t_pos	center;
	int		i;
	int		x;
	int		y;

	center.x = MINI_W / 2;
	center.y = MINI_H / 2;
	i = 0;
	while (i < 10)
	{
		x = center.x + i * cos(game->player->direction);
		y = center.y + i * sin(game->player->direction);
		my_pixel_put(game->img, x, y, 0xFF00FF00);
		i++;
	}
}

static void	draw_player(t_game *game)
{
	t_pos	center;
	int		x;
	int		y;

	center.x = MINI_W / 2;
	center.y = MINI_H / 2;
	y = center.y - PLAYER_SIZE;
	while (y < center.y + PLAYER_SIZE)
	{
		x = center.x - PLAYER_SIZE;
		while (x < center.x + PLAYER_SIZE)
		{
			if (pow(x - center.x, 2) + pow(y - center.y, 2) < 8)
				my_pixel_put(game->img, x, y, 0xFF055555);
			x++;
		}
		y++;
	}
}

static void	render_minimap(t_game *game, t_pos *map, int x, int y)
{
	if (map->y >= 0 && map->x >= 0
		&& map->x < game->data->height
		&& map->y < game->data->width)
	{
		if (game->data->map[map->y][map->x] == '1')
			my_pixel_put(game->img, x, y, 0xFF000000);
		else if (game->data->map[map->y][map->x] == 'D')
			my_pixel_put(game->img, x, y, 0x7FFF00FF);
		else
			my_pixel_put(game->img, x, y, 0xFFFFFFFF);
	}
	else
		my_pixel_put(game->img, x, y, 0xFF000000);
}

void	draw_minimap(t_game *game)
{
	t_pos	player;
	t_pos	map;
	int		y;
	int		x;

	player.x = (game->player->start.x / TILE_SIZE) * MINI_S - MINI_W / 2;
	player.y = (game->player->start.y / TILE_SIZE) * MINI_S - MINI_H / 2;
	y = 0;
	while (y < MINI_H)
	{
		x = 0;
		while (x < MINI_W)
		{
			map.x = (x + player.x) / MINI_S;
			map.y = (y + player.y) / MINI_S;
			if (pow(x - RADIUS, 2)
				+ pow(y - RADIUS, 2) <= pow(RADIUS, 2))
				render_minimap(game, &map, x, y);
			x++;
		}
		y++;
	}
	draw_player(game);
	draw_player_direction(game);
}
