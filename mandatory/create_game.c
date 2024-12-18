/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-omra <hel-omra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 00:34:06 by hel-omra          #+#    #+#             */
/*   Updated: 2024/12/15 00:34:07 by hel-omra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	load_textures(t_game *game)
{
	game->tx->e = mlx_load_png(game->data->ea);
	game->tx->w = mlx_load_png(game->data->we);
	game->tx->s = mlx_load_png(game->data->so);
	game->tx->n = mlx_load_png(game->data->no);
	if (!game->tx->e || !game->tx->w || !game->tx->s || !game->tx->n)
		exiting(game, "Invalid texture");
}

static void	update(void *p)
{
	t_game	*game;

	game = p;
	movement(game, 0, 0);
	raycasting(game);
}

static void	set_player(t_game *game)
{
	char	c;

	c = game->data->player_facing;
	if (c == 'E')
		game->player->direction = 0;
	else if (c == 'N')
		game->player->direction = (3 * M_PI) / 2;
	else if (c == 'W')
		game->player->direction = M_PI;
	else if (c == 'S')
		game->player->direction = M_PI / 2;
	game->player->start.x = (game->data->player_postion.x * TILE_SIZE)
		+ TILE_SIZE / 2;
	game->player->start.y = (game->data->player_postion.y * TILE_SIZE)
		+ TILE_SIZE / 2;
	game->player->view = FOV * (M_PI / 180);
	game->player->walk = STOP;
	game->player->turn = STOP;
}

static void	protect_macros(t_game *game)
{
	if (WIDTH < 150 || WIDTH > 2560 || HEIGHT < 150 || HEIGHT > 1440)
		exiting(game, "Invalid resolution");
	if (FOV < 60 || FOV > 90)
		exiting(game, "Invalid FOV (between 60 ~ 90)");
}

void	create_game(t_game *game)
{
	protect_macros(game);
	game->win = mlx_init(WIDTH, HEIGHT, "cub3D", true);
	if (!game->win)
		exiting(game, "mlx failed");
	game->img = mlx_new_image(game->win, WIDTH, HEIGHT);
	if (!game->img)
		exiting(game, "mlx img failed");
	if (mlx_image_to_window(game->win, game->img, 0, 0) == -1)
		exiting(game, "mlx img to window failed");
	load_textures(game);
	set_player(game);
	mlx_loop_hook(game->win, update, game);
	mlx_key_hook(game->win, handle_key, game);
	mlx_loop(game->win);
}
