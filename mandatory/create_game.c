/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbesbess <tbesbess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 10:28:17 by tbesbess          #+#    #+#             */
/*   Updated: 2024/10/27 12:08:49 by tbesbess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_clear_img(mlx_image_t *img)
{
	u_int32_t	i;
	u_int16_t	j;

	i = 0;
	while (i < img->height)
	{
		j = 0;
		while (j < img->width)
		{
			mlx_put_pixel(img, j, i, 0);
			j++;
		}
		i++;
	}
}

void update(void *p)
{
	t_game	*game;

	game = p;
	ft_clear_img(game->img);
	// mlx_resize_image(game->img, game->win->width, game->win->height); SOS
	movement(game, 0, 0);
	// animation(game);
	raycasting(game);
}

void	set_player(t_game *game)
{
	char	c;

	game->player = malloc(sizeof(t_pl));
	c = game->data->player_facing;
	if (c == 'E')
		game->player->direction = 0;
	else if (c == 'N')
		game->player->direction = (3 * M_PI) / 2;
	else if (c == 'W')
		game->player->direction = M_PI;
	else if (c == 'S')
		game->player->direction = M_PI / 2;
	game->player->start.x = (game->data->player_postion.x * TILE_SIZE) + TILE_SIZE / 2;
	game->player->start.y = (game->data->player_postion.y * TILE_SIZE) + TILE_SIZE / 2;
	game->player->view = FOV * (M_PI / 180);
	game->player->walk = STOP;
	game->player->turn = STOP;
}

void create_game(t_game *game)
{
	game->win = mlx_init(WIDTH, HEIGHT, "cub3D", true);
    if (!game->win)
        (ft_putstr_fd("Error\n", 2), exit(2));
	game->img = mlx_new_image(game->win, WIDTH, HEIGHT);
    if (!game->img)
        (ft_putstr_fd("Error\n", 2), exit(2));
	if (mlx_image_to_window(game->win, game->img, 0, 0) < 0)
        (ft_putstr_fd("Error\n", 2), exit(2));
	// load_textures(game);
	set_player(game);
	mlx_loop_hook(game->win, &update, game);
	// mlx_loop_hook(game->win, &animation, game);
	mlx_key_hook(game->win, &handle_key, game);
	mlx_loop(game->win);
}