/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_b.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-omra <hel-omra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 00:32:39 by hel-omra          #+#    #+#             */
/*   Updated: 2024/12/15 00:32:40 by hel-omra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_b.h"

static void	check_elements(t_data *data)
{
	int		x;
	int		y;
	int		count;

	y = -1;
	count = 0;
	while (data->map[++y])
	{
		x = -1;
		while (data->map[y][++x])
		{
			if (!ft_strchr("10 WESND", data->map[y][x]))
				exiting(data->game, "Invalid map");
			if (ft_strchr("WESN", data->map[y][x]))
			{
				data->player_postion.x = x;
				data->player_postion.y = y;
				(1) && (data->player_facing = data->map[y][x], count++);
			}
		}
	}
	if (count != 1)
		exiting(data->game, "Invalid Player Position");
}

static void	check_doors(t_game *game, int y, int x)
{
	int		hz;
	int		vr;
	char	**s;

	hz = 0;
	vr = 0;
	s = game->data->map;
	if (s[y - 1][x] == '1' && s[y + 1][x] == '1')
		hz = 1;
	if (s[y][x - 1] == '1' && s[y][x + 1] == '1')
		vr = 1;
	if (!hz && !vr)
		exiting(game, "Invalid door");
}

static void	check_space(char **map, t_game *game)
{
	size_t		y;
	size_t		x;

	y = 1;
	while (map[y])
	{
		x = 1;
		while (map[y][x])
		{
			if (ft_strchr("WESN0D", map[y][x]))
			{
				if (ft_strlen(map[y - 1]) - 1 < x
					|| ft_strlen(map[y + 1]) - 1 < x)
					exiting(game, "Invalid map");
				if (map[y][x - 1] == ' ' || map[y][x + 1] == ' '
					|| map[y - 1][x] == ' ' || map[y + 1][x] == ' ')
					exiting(game, "Invalid map");
				if (map[y][x] == 'D')
					check_doors(game, y, x);
			}
			x++;
		}
		y++;
	}
}

static void	get_map_ready(t_data *data)
{
	int		len;
	int		tmp;
	int		i;
	char	*str;

	(1) && (i = -1, len = 0, tmp = 0);
	while (data->map[++i])
	{
		tmp = len;
		len = ft_strlen(data->map[i]);
		if (tmp > len)
			len = tmp;
	}
	i = -1;
	while (data->map[++i])
	{
		tmp = len - ft_strlen(data->map[i]);
		while (tmp--)
		{
			str = data->map[i];
			data->map[i] = ft_strjoin(data->map[i], " ");
		}
	}
	data->height = len;
	data->width = ft_strlen2d(data->map);
}

void	parse_it(char *s, t_game *game)
{
	game->data->game = game;
	store_instructions(s, game->data);
	check_empty_map(game->data);
	store_map(game->data);
	get_map_ready(game->data);
	check_elements(game->data);
	check_walls(game->data->map, game);
	check_space(game->data->map, game);
}
