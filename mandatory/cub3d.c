/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-omra <hel-omra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 00:34:09 by hel-omra          #+#    #+#             */
/*   Updated: 2024/12/15 00:34:09 by hel-omra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	exiting(t_game *game, char *message)
{
	if (game->tx->e)
		mlx_delete_texture(game->tx->e);
	if (game->tx->w)
		mlx_delete_texture(game->tx->w);
	if (game->tx->s)
		mlx_delete_texture(game->tx->s);
	if (game->tx->n)
		mlx_delete_texture(game->tx->n);
	if (game->win)
		mlx_terminate(game->win);
	close(game->data->fd);
	ft_malloc(0, FREE);
	if (message)
		(printf(RED"%s !\n" RESET, message), exit(1));
	exit(0);
}

static void	check_input(int ac, char **av)
{
	if (ac != 2 || ft_strlen(av[1]) < 4
		|| ft_strcmp(".cub", av[1] + ft_strlen(av[1]) - 4) != 0)
	{
		ft_putstr_fd("./cub3D_bonus + \"map path\"\n"RESET, 2);
		exit(1);
	}
}

static void	allocate_t_game(t_game **game)
{
	(*game) = ft_malloc(sizeof(t_game), MALLOC);
	(*game)->data = ft_malloc(sizeof(t_data), MALLOC);
	(*game)->rays = ft_malloc(sizeof(t_ray), MALLOC);
	(*game)->player = ft_malloc(sizeof(t_pl), MALLOC);
	(*game)->tx = ft_malloc(sizeof(t_tx), MALLOC);
}

int	main(int ac, char **av)
{
	t_game	*game;

	check_input(ac, av);
	allocate_t_game(&game);
	parse_it(av[1], game);
	create_game(game);
	exiting(game, NULL);
}
