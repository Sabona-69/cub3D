#include "../../include/cub3d.h"

void	check_sides(char **map, t_game *game)
{
	int		y;
	int		x;
	int		x_len;

	y = 1;
	while (map[y])
	{
		x_len = ft_strlen(map[y]) - 1;
		x = skip_char(map[y], ' ');
		if (is_empty(map[y]) == FALSE && (!ft_strchr("1 ", map[y][x_len])
			|| !ft_strchr("1 ", map[y][0])))
			exiting(game, "Invalid map");
		y++;
	}
}

void	check_walls(char **map, t_game *game)
{
	int		y;
	int		x;

	x = skip_char(map[0], ' ');
	while (map[0][x])
	{
		if (!ft_strchr("1 ", map[0][x]))
			exiting(game, "Invalid map");
		x++;
	}
	y = game->data->width - 1;
	x = skip_char(map[y], ' ');
	while (map[y][x])
	{
		if (!ft_strchr("1 ", map[y][x]))
			exiting(game, "Invalid map");
		x++;
	}
	check_sides(map, game);
}

void	check_empty_map(t_data *data)
{
	char	*tmp;

	while (data->line)
	{
		tmp = ft_strtrim(data->line, "\n");
		if (!is_empty(tmp))
			break ;
		data->line = get_next_line(data->fd);
	}
	if (!data->line)
		return (exiting(data->game, "Empty map"));
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
			data->line = ft_strdup(" ");
		if (min_len < line_start)
			line_start = min_len;
		if (data->line[0] == ' ')
			min_len = skip_char(data->line, ' ');
		else if (data->line[0])
			min_len = 0;
		map = strjoin2d(map, data->line);
		data->line = get_next_line(data->fd);
	}
	min_len = -1;
	while (map[++min_len])
		data->map = strjoin2d(data->map, &(map[min_len][line_start]));
}