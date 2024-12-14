/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-omra <hel-omra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 00:34:14 by hel-omra          #+#    #+#             */
/*   Updated: 2024/12/15 00:34:16 by hel-omra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	key_release(mlx_key_data_t keydata, t_game *game)
{
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_RELEASE))
		game->player->walk = STOP;
	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_RELEASE))
		game->player->walk = STOP;
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_RELEASE))
		game->player->walk = STOP;
	else if (keydata.key == MLX_KEY_W && (keydata.action == MLX_RELEASE))
		game->player->walk = STOP;
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_RELEASE)
		game->player->turn = STOP;
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_RELEASE)
		game->player->turn = STOP;
}

void	handle_key(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = param;
	if (keydata.key == MLX_KEY_ESCAPE && (keydata.action == MLX_PRESS))
		exiting(game, NULL);
	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS))
		game->player->walk = LEFT;
	else if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS))
		game->player->walk = RIGHT;
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS))
		game->player->walk = DOWN;
	else if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		game->player->walk = UP;
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		game->player->turn = TURN_LEFT;
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		game->player->turn = TURN_RIGHT;
	key_release(keydata, game);
}

void	my_pixel_put(mlx_image_t *img, int x, int y, int color)
{
	if (x < 0)
		return ;
	else if ((uint32_t)x >= img->width)
		return ;
	if (y < 0)
		return ;
	else if ((uint32_t)y >= img->height)
		return ;
	mlx_put_pixel(img, x, y, color);
}

void	adjust_step(t_game *game, t_pos_d *delta, int is_vertical)
{
	if (is_vertical)
	{
		if (game->rays->left)
			delta->x *= -1;
		if (game->rays->up && delta->y > 0)
			delta->y *= -1;
		if (game->rays->down && delta->y < 0)
			delta->y *= -1;
	}
	else
	{
		if (game->rays->up)
			delta->y *= -1;
		if (game->rays->left && delta->x > 0)
			delta->x *= -1;
		if (game->rays->right && delta->x < 0)
			delta->x *= -1;
	}
}
