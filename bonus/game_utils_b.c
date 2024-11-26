/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils_b.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-omra <hel-omra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 10:27:11 by tbesbess          #+#    #+#             */
/*   Updated: 2024/11/26 02:05:08 by hel-omra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_b.h"

int	check_collision(t_game *game, int x, int y)
{
	int	top_left;
	int	top_right;
	int	bottom_left;
	int	bottom_right;

	top_left = is_wall(x - COLLISION, y - COLLISION, game);
	top_right = is_wall(x + COLLISION, y - COLLISION, game);
	bottom_left = is_wall(x - COLLISION, y + COLLISION, game);
	bottom_right = is_wall(x + COLLISION, y + COLLISION, game);
	return (top_left || top_right || bottom_left || bottom_right);
}

double	normalize_angle(double angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}

double	calcul_distance(t_pos_d start, t_pos_d end)
{
	return (sqrt(pow(start.x - end.x, 2) + pow(start.y - end.y, 2)));
}

int	ft_get_color(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a << 0);
}

int	reverse_bytes(int c)
{
	int	b;

	b = 0;
	b |= (c & 0xFF) << 24;
	b |= (c & 0xFF00) << 8;
	b |= (c & 0xFF0000) >> 8;
	b |= (c & 0xFF000000) >> 24;
	return (b);
}

int	is_wall(double x, double y, t_game *game)
{
	t_pos	m;

	if (x < 0 || y < 0)
		return (1);
	m.x = floor(x / TILE_SIZE);
	m.y = floor(y / TILE_SIZE);
	if (m.y < 0 || m.y >= game->data->width
		|| m.x < 0 || m.x >= game->data->height)
		return (1);
	if (game->data->map[m.y][m.x] == '1' || game->data->map[m.y][m.x] == 'D')
	{
		if (game->data->map[m.y][m.x] == 'D')
			game->door->hit_door = 1;
		else
			game->door->hit_door = 0;
		return (1);
	}
	return (0);
}
