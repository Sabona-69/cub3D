#include "../../include/cub3d_b.h"

void	check_sides(char **map, int x_len, t_game *game)
{
	int		y;
	int		x;

	y = 1;
	while (map[y])
	{
		x_len = ft_strlen(map[y]) - 1;
		x = skip_char(map[y], ' ');
		if (is_empty(map[y]) == FALSE && (!ft_strchr("1 ", map[y][x_len])
			|| !ft_strchr("1 ", map[y][x_len])))
			exiting(game, "Invalid map", PARSE);
		y++;
	}
}

void	check_walls(char **map, t_game *game)
{
	int		y_len;
	int		x_len;
	int		y;
	int		x;

	x = skip_char(map[0], ' ');
	while (map[0][x])
	{
		if (!ft_strchr("1 ", map[0][x]))
			exiting(game, "Invalid map", PARSE);
		x++;
	}
	y_len = game->data->width - 1;
	x = skip_char(map[y_len], ' ');
	while (map[y_len][x])
	{
		if (!ft_strchr("1 ", map[y_len][x]))
			exiting(game, "Invalid map", PARSE);
		x++;
	}
	check_sides(map, x_len, game);
}

void	check_empty_map(t_data *data)
{
	char	*tmp;

	while (data->line)
	{
		tmp = ft_strtrim(data->line, "\n");
		if (!is_empty(tmp))
			break ;
		free(data->line);
		free(tmp);
		data->line = get_next_line(data->fd);
	}
	free(tmp);
	if (!data->line)
		return (exiting(data->game, "Empty map", PARSE));
}

void	store_map(t_data *data)
{
	char	*tmp;
	char	**map;
	int		min_len;
	int		line_start;

	(1) && (map = NULL, min_len = ft_strlen(data->line), line_start = min_len);
	while (data->line)
	{
		tmp = data->line;
		data->line = ft_strtrim_end(data->line, " \n");
		if (!data->line[0])
			(free(data->line), data->line = ft_strdup(" "));
		if (min_len < line_start)
			line_start = min_len;
		if (data->line[0] == ' ')
			min_len = skip_char(data->line, ' ');
		else if (data->line[0])
			min_len = 0;
		map = strjoin2d(map, data->line);
		(free(tmp), free(data->line), data->line = get_next_line(data->fd));
	}
	(free(data->line), min_len = -1);
	while (map[++min_len])
		data->map = strjoin2d(data->map, &(map[min_len][line_start]));
	free2d(map, ft_strlen2d(map));
}
