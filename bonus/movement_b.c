/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_b.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-omra <hel-omra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 12:22:45 by tbesbess          #+#    #+#             */
/*   Updated: 2024/12/15 00:33:27 by hel-omra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_b.h"

static void	open_the_door(t_game *game)
{
	t_pos_d		front;
	t_pos		m;
	double		angle;

	angle = game->player->direction;
	front.x = game->player->start.x + cos(angle) * TILE_SIZE;
	front.y = game->player->start.y + sin(angle) * TILE_SIZE;
	m.x = floor(front.x / TILE_SIZE);
	m.y = floor(front.y / TILE_SIZE);
	if (game->data->map[m.y][m.x] == 'D' && game->door->is_open)
	{
		game->pid_door = fork();
		if (game->pid_door == 0)
			play_sound(DOOR_ENTER);
		else
		{
			if (game->door->is_closed)
			{
				game->door->pos.x = m.x;
				game->door->pos.y = m.y;
				game->door->is_closed = 0;
				game->data->map[m.y][m.x] = '0';
			}
		}
	}
}

static void	close_the_door(t_game *game)
{
	t_pos_d		player;
	t_pos_d		door;
	double		distance;

	player.x = game->player->start.x;
	player.y = game->player->start.y;
	door.x = (game->door->pos.x + 0.5) * TILE_SIZE;
	door.y = (game->door->pos.y + 0.5) * TILE_SIZE;
	distance = sqrt(pow(player.x - door.x, 2) + pow(player.y - door.y, 2));
	if (distance >= TILE_SIZE)
	{
		game->data->map[game->door->pos.y][game->door->pos.x] = 'D';
		game->door->is_closed = 1;
	}
}

static void	walk_player(t_game *game, double move_x, double move_y)
{
	int	new_x;
	int	new_y;

	new_x = round(game->player->start.x + move_x);
	new_y = round(game->player->start.y + move_y);
	if (game->door->is_open)
	{
		open_the_door(game);
		game->door->is_open = 0;
	}
	if (!check_collision(game, new_x, game->player->start.y))
		game->player->start.x = new_x;
	if (!check_collision(game, game->player->start.x, new_y))
		game->player->start.y = new_y;
	if (!game->door->is_closed)
		close_the_door(game);
}

void	turn(t_game *game, t_status status)
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
