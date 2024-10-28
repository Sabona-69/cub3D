/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbesbess <tbesbess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 10:27:11 by tbesbess          #+#    #+#             */
/*   Updated: 2024/10/27 13:23:50 by tbesbess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	if (game->data->map[m.y][m.x] == '1')
		return (1);
	return (0);
}
