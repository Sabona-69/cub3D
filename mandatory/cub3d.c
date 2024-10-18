/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbesbess <tbesbess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:10:45 by tbesbess          #+#    #+#             */
/*   Updated: 2024/10/18 10:10:45 by tbesbess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void set_player(t_game *game)
{
    char c;

    game->player = malloc(sizeof(t_pl));
    if (!game->player) {
        fprintf(stderr, "Memory allocation failed for player.\n");
        exit(EXIT_FAILURE);
    }

    if (!game->data || !game->data->map) {
        fprintf(stderr, "Map data not initialized properly.\n");
        exit(EXIT_FAILURE);
    }

    c = game->data->map[game->data->player_postion.y][game->data->player_postion.x];
    if (c == 'E')
        game->player->derection = 0;
    else if (c == 'N')
        game->player->derection = (3 * M_PI) / 2;
    else if (c == 'W')
        game->player->derection = M_PI;
    else if (c == 'S')
        game->player->derection = M_PI / 2;

    printf("Setting player direction: %c\n", c);
    game->player->star.x = (game->data->player_postion.x * TILE_SIZE) + TILE_SIZE / 2;
    game->player->star.y = (game->data->player_postion.y * TILE_SIZE) + TILE_SIZE / 2;
    game->player->view = VIEW * (M_PI / 180);
    game->player->walk = STOP;
    game->player->turn = STOP;
}

void    create_game(t_game *game)
{
    int32_t     window_w;
    int32_t     window_h;
    game->win = mlx_init(WIDTH, HEIGHT, "cub3d", false);
    if (!game->win)
        printf("error init\n");
    window_w = game->win->width;
    window_h = game->win->height;
    game->img = mlx_new_image(game->win, window_w, window_h);
    if (!game->img)
        printf("error img\n");
    if (mlx_image_to_window(game->win, game->img, 0, 0) == -1)
        printf("error image to window");
    set_player(game);
  
}

int main(int ac, char **av)
{
	t_data  *cub;
    t_game  *game;
    int i = 0;


	if (ac != 2 || ft_strlen(av[1]) < 4 || ft_strcmp(".cub", av[1] + ft_strlen(av[1]) - 4) != 0)
		return (printf("Please Insert \"./cub\" + valid map\n"), 1);
	cub = malloc(sizeof(t_data));
	if (!cub)
		return (ft_putstr_fd("malloc failed ", 2), 1);
	ft_memset(cub, 0, sizeof(t_data));
	parse_it(av[1], cub);
    game = malloc(sizeof(t_game));
	ft_memset(game, 0, sizeof(t_game));
    game->data = cub;
    while (game->data->map[i])
        printf ("[%s]\n", game->data->map[i++]);
	create_game(game);
	exiting(cub, 0);
}