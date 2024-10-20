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
        game->player->direction = 0;
    else if (c == 'N')
        game->player->direction = (3 * M_PI) / 2;
    else if (c == 'W')
        game->player->direction = M_PI;
    else if (c == 'S')
        game->player->direction = M_PI / 2;
    game->player->star.x = (game->data->player_postion.x * TILE_SIZE) + TILE_SIZE / 2;
    game->player->star.y = (game->data->player_postion.y * TILE_SIZE) + TILE_SIZE / 2;
    game->player->view = VIEW * (M_PI / 180);
    game->player->walk = STOP;
    game->player->turn = STOP;
}

int handle_key(int keycode, t_game *game){
    if (keycode == MLX_KEY_ESCAPE) { // ESC key
        // game->isGameRunning = FALSE;
		exit(1);
    }
    if (keycode == MLX_KEY_W) { 
		game->player->move.x += cos(game->player->direction) * MOVE_SPEED;
		game->player->move.y += sin(game->player->direction) * MOVE_SPEED;
	}
	if (keycode == MLX_KEY_S) { 
		game->player->move.x -= cos(game->player->direction) * MOVE_SPEED;
		game->player->move.y -= sin(game->player->direction) * MOVE_SPEED;
	}
	if (keycode == MLX_KEY_D) { // D key
        game->player->turn = LEFT;
    }
    if (keycode == MLX_KEY_A) { // A key
        game->player->turn = RIGHT;
    }
    return 0;
}

void update(t_game *game)
{
	
}
void create_game(t_game *game)
{
    int32_t window_w;
    int32_t window_h;

    game->win = mlx_init(WIDTH, HEIGHT, "cub3d", false);
    window_w = game->win->width ;
    window_h = game->win->height;
    game->img = mlx_new_image(game->win, window_w, window_h);
	mlx_image_to_window(game->win, game->img, 0, 0);
    set_player(game);
	mlx_key_hook(game->win, handle_key, game);
	mlx_loop_hook(game->win, update, game);
	// mlx_new_image();
    mlx_loop(game->win);
}

int main(int ac, char **av)
{
	t_data  *cub;
    t_game  *game;


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
    int i = 0;
    while (game->data->map[i])
        printf ("[%s]\n", game->data->map[i++]);
	create_game(game);
	exiting(cub, 0);
}