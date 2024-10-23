#include "../cub3d.h"

void	exiting(t_data *cub, int status)
{
	free(cub->EA);
	free(cub->WE);
	free(cub->SO);
	free(cub->NO);
	if (cub->map)
		free2d(cub->map, ft_strlen2d(cub->map));
	free(cub->line);
	close(cub->fd);
	if (status == 0)
		exit(0);
	ft_putstr_fd(RED"Error\n"RESET, 2);
	exit(1);
}

void	store_map(t_data *cub)
{
	char *tmp;
	char **map;
	int i;
	int j;

	map = NULL;
	while (cub->line)
	{
		tmp = ft_strtrim(cub->line, "\n");
		if (!is_empty(tmp))
			break ;
		free(cub->line);
		free(tmp);
		cub->line = get_next_line(cub->fd);
	}
	if (!cub->line)
		return (exiting(cub, 1));
	i = ft_strlen(cub->line);
	j = i;
	free(tmp);
	while (cub->line)
	{
		tmp = cub->line;
		cub->line = ft_strtrim_end(cub->line, " \n");
		if (!cub->line[0])
			(free(cub->line), cub->line = ft_strdup(" "));
		if (i < j)
			j = i;
		if (cub->line[0] == ' ')
			i = skip_char(cub->line, ' ');
		else if (cub->line[0])
			i = 0;
		map = strjoin2d(map, cub->line);
		free(tmp);
		free(cub->line);
		cub->line = get_next_line(cub->fd);
	}
	i = -1;
	// free(tmp);
	free(cub->line);
	while (map[++i])
		cub->map = strjoin2d(cub->map, &(map[i][j]));
	free2d(map, ft_strlen2d(map));
}



void	check_elements(t_data *cub)
{
	int		x;
	int		y;
	int		count;

	y = 0;
	count = 0;
	while (cub->map[y])
	{
		x = 0;
		while (cub->map[y][x])
		{
			if (!ft_strchr("10 WESN", cub->map[y][x]))
				exiting(cub, 1);
			if (ft_strchr("WESN", cub->map[y][x]))
			{
				cub->player_postion.x = x;
				cub->player_postion.y = y;
				(1) && (cub->player_facing = cub->map[y][x], count++);
			}
			x++;
		}
		y++;
	}
	if (count != 1)
		exiting(cub, 1);
}

void check_walls(char **map, t_data *cub)
{
	int		y_len;
	int		x_len;
	int		y;
	int		x;

	x = skip_char(map[0], ' ');
	while (map[0][x])
	{
		if (map[0][x] != '1' && map[0][x] != ' ')
			exiting(cub, 1);
		x++;
	}
	y_len = ft_strlen2d(map) - 1;
	x = skip_char(map[y_len], ' ');
	while (map[y_len][x])
	{
		if (map[y_len][x] != '1' && map[y_len][x] != ' ')
			exiting(cub, 1);
		x++;
	}
	y = 1;
	while (map[y])
	{
		x_len = ft_strlen(map[y]) - 1;
		x = skip_char(map[y], ' ');
		if (is_empty(map[y]) == FALSE && (map[y][x] != '1' || map[y][x_len] != '1'))
			exiting(cub, 1);
		y++;
	}
}

void check_space(char **map, t_data *cub)
{
	size_t		y;
	size_t		x;

	y = 1;
	while (map[y])
	{
		x = 1;
		while (map[y][x])
		{
			if (ft_strchr("WESN0", map[y][x]))
			{
				if (ft_strlen(map[y - 1]) - 1 < x || ft_strlen(map[y + 1]) - 1 < x)
					exiting(cub, 1);
				if (map[y][x - 1] == ' ' || map[y][x + 1] == ' ' || map[y - 1][x] == ' ' || map[y + 1][x] == ' ')
					exiting(cub, 1);
			}
			x++;
		}
		y++;
	}
}

void	get_map_ready(t_data *cub)
{
	int		len;
	int		tmp;
	int		i;
	char	*str;

	i = -1;
	len = 0;
	tmp = 0;
	while (cub->map[++i])
	{
		tmp = len; // 0
		len = ft_strlen(cub->map[i]); // 10 
		if (tmp > len)
			len = tmp;
	}
	i = -1;
	while (cub->map[++i])
	{
		tmp = len - ft_strlen(cub->map[i]);
		while (tmp--)
		{
			str = cub->map[i];
			cub->map[i] = ft_strjoin(cub->map[i], " ");
			free(str);
		}
	}
	cub->height = len;
	cub->width = ft_strlen2d(cub->map);
}

void parse_it(char *s, t_data *cub)
{
	store_instructions(s, cub);
	store_map(cub);
	check_elements(cub);
	check_walls(cub->map, cub);
	check_space(cub->map, cub);
	get_map_ready(cub);
	close(cub->fd);
	// printf("{{%c}}\n", cub->map[0][ft_strlen(cub->map[0]) - 1]);
	// printf("<%s>\n", cub->EA);
	// 	printf("<%s>\n", cub->NO);
	// 	printf("<%s>\n", cub->SO);
	// 	printf("<%s>\n", cub->WE);
	// 	printf("%d %d %d \n", cub->C[0], cub->C[1], cub->C[2]);
	// int i = 0;
	// while (cub->map[i])
		// printf("{{%s}}\n", cub->map[i++]);
}