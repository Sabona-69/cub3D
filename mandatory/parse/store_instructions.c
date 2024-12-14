/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_instructions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-omra <hel-omra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 00:34:00 by hel-omra          #+#    #+#             */
/*   Updated: 2024/12/15 00:34:02 by hel-omra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static char	*get_texture_line(char *s, t_game *game)
{
	char	**split;
	char	*new;
	int		check;

	split = ft_split(s, " ");
	if (ft_strlen2d(split) != 2)
		exiting(game, "Invalid texture");
	new = ft_strdup(split[1]);
	if (!new)
		return (NULL);
	check = open(new, O_RDONLY);
	close(check);
	if (check == -1)
		exiting(game, "Invalid texture Path");
	return (new);
}

static void	get_colors(int *tab, char *s, t_game *game)
{
	char	**split;
	char	*tmp;
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (s[++i])
		if (s[i] == ',')
			j++;
	if (j != 2)
		exiting(game, "Must separate with 1 comma");
	split = ft_split(s, ",");
	if (ft_strlen2d(split) != 3)
		exiting(game, "Set only 3 colors");
	i = -1;
	while (++i < 3)
	{
		tmp = ft_strtrim(split[i], " ");
		tab[i] = ft_atoi(tmp);
	}
	if (tab[0] == -1 || tab[1] == -1 || tab[2] == -1)
		exiting(game, "Invalid colors (0 ~ 255)");
}

static int	check_line(t_data *data, char *tmp)
{
	if (ft_strncmp("NO ", tmp, 3) == 0 && !data->no)
		data->no = get_texture_line(tmp, data->game);
	else if (ft_strncmp("SO ", tmp, 3) == 0 && !data->so)
		data->so = get_texture_line(tmp, data->game);
	else if (ft_strncmp("WE ", tmp, 3) == 0 && !data->we)
		data->we = get_texture_line(tmp, data->game);
	else if (ft_strncmp("EA ", tmp, 3) == 0 && !data->ea)
		data->ea = get_texture_line(tmp, data->game);
	else if (ft_strncmp("F ", tmp, 2) == 0)
		get_colors(data->f, tmp + 2, data->game);
	else if (ft_strncmp("C ", tmp, 2) == 0)
		get_colors(data->c, tmp + 2, data->game);
	else
		return (0);
	return (1);
}

void	store_instructions(char *s, t_data *data)
{
	char	*tmp;
	int		i;

	data->fd = open(s, O_RDONLY);
	if (data->fd == -1)
		exiting(data->game, "Can't open map");
	i = 0;
	data->line = get_next_line(data->fd);
	while (data->line)
	{
		tmp = ft_strtrim(data->line, " \n");
		if (check_line(data, tmp))
			i++;
		else if (i != 6 && tmp[0])
			exiting(data->game, "Invalid Ins");
		data->line = get_next_line(data->fd);
		if (i == 6)
			break ;
	}
	if (i != 6 || data->c[0] == -1 || data->f[0] == -1 || !data->ea
		|| !data->no || !data->so || !data->we)
		exiting(data->game, "Invalid map");
}
