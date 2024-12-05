/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-omra <hel-omra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 12:22:45 by tbesbess          #+#    #+#             */
/*   Updated: 2024/12/05 11:18:27 by hel-omra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	check_collision(t_game *game, int x, int y)
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

static void	walk_player(t_game *game, double move_x, double move_y)
{
	int	new_x;
	int	new_y;

	new_x = round(game->player->start.x + move_x);
	new_y = round(game->player->start.y + move_y);
	if (!check_collision(game, new_x, game->player->start.y))
		game->player->start.x = new_x;
	if (!check_collision(game, game->player->start.x, new_y))
		game->player->start.y = new_y;
}

double	normalize_angle(double angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}

static void	turn(t_game *game, t_status status)
{
	if (status == RIGHT)
		game->player->direction += ROTATION_SPEED;
	else if (status == LEFT)
		game->player->direction -= ROTATION_SPEED;
	game->player->direction = normalize_angle(game->player->direction);
}

void	movement(t_game *game, double move_x, double move_y)
{
	if (game->player->turn == TURN_RIGHT)
		turn(game, RIGHT);
	else if (game->player->turn == TURN_LEFT)
		turn(game, LEFT);
	if (game->player->walk == RIGHT)
	{
		move_x = -sin(game->player->direction) * MOVE_SPEED;
		move_y = cos(game->player->direction) * MOVE_SPEED;
	}
	else if (game->player->walk == LEFT)
	{
		move_x = sin(game->player->direction) * MOVE_SPEED;
		move_y = -cos(game->player->direction) * MOVE_SPEED;
	}
	else if (game->player->walk == DOWN)
	{
		move_x = -cos(game->player->direction) * MOVE_SPEED;
		move_y = -sin(game->player->direction) * MOVE_SPEED;
	}
	else if (game->player->walk == UP)
	{
		move_x = cos(game->player->direction) * MOVE_SPEED;
		move_y = sin(game->player->direction) * MOVE_SPEED;
	}
	walk_player(game, move_x, move_y);
}
