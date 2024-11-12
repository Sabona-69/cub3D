#include "../../include/cub3d_b.h"

char	*get_texture_line(char *s, t_game *game)
{
	char	**split;
	char	*new;
	int		check;

	split = ft_split(s, " ");
	if (ft_strlen2d(split) != 2)
		exiting(game, "Invalid texture", PARSE);
	new = ft_strdup(split[1]);
	free2d(split, ft_strlen2d(split));
	check = open(new, O_RDONLY);
	close(check);
	if (check == -1)
		exiting(game, "Invalid texture Path", PARSE);
	return (new);
}

void	get_colors(int *tab, char *s, t_game *game)
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
		exiting(game, "Must separate with 1 comma", PARSE);
	split = ft_split(s, ",");
	if (ft_strlen2d(split) != 3)
		exiting(game, "Set only 3 colors", PARSE);
	i = -1;
	while (++i < 3)
	{
		tmp = ft_strtrim(split[i], " ");
		tab[i] = my_atoi(tmp);
		free(tmp);
	}
	if (tab[0] == -1 || tab[1] == -1 || tab[2] == -1)
		exiting(game, "Invalid colors (0 ~ 255)", PARSE);
	free2d(split, ft_strlen2d(split));
}

int	check_line(t_data *data, char *tmp)
{
	if (ft_strncmp("NO ", tmp, 3) == 0)
		data->no = get_texture_line(tmp, data->game);
	else if (ft_strncmp("SO ", tmp, 3) == 0)
		data->so = get_texture_line(tmp, data->game);
	else if (ft_strncmp("WE ", tmp, 3) == 0)
		data->we = get_texture_line(tmp, data->game);
	else if (ft_strncmp("EA ", tmp, 3) == 0)
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
		exiting(data->game, "Can't open map", PARSE);
	(1) && (i = 0, data->line = get_next_line(data->fd));
	while (data->line)
	{
		tmp = ft_strtrim(data->line, " \n");
		if (check_line(data, tmp))
			i++;
		else if (i != 6 && tmp[0])
			(free(tmp), exiting(data->game, "Invalid map", PARSE));
		(free(tmp), free(data->line));
		data->line = get_next_line(data->fd);
		if (i == 6)
			break ;
	}
	if (i != 6 || data->c[0] == -1 || data->f[0] == -1 || !data->ea
		|| !data->no || !data->so || !data->we)
		exiting(data->game, "Can't open map", PARSE);
}
