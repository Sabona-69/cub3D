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

void	check_elements(t_data *cub)
{
	int		x;
	int		y;
	int		count;

	y = -1;
	count = 0;
	while (cub->map[++y])
	{
		x = -1;
		while (cub->map[y][++x])
		{
			if (!ft_strchr("10 WESN", cub->map[y][x]))
				exiting(cub, 1);
			if (ft_strchr("WESN", cub->map[y][x]))
			{
				cub->player_postion.x = x;
				cub->player_postion.y = y;
				(1) && (cub->player_facing = cub->map[y][x], count++);
			}
		}
	}
	if (count != 1)
		exiting(cub, 1);
}

void	check_space(char **map, t_data *cub)
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
				if (ft_strlen(map[y - 1]) - 1 < x
					|| ft_strlen(map[y + 1]) - 1 < x)
					exiting(cub, 1);
				if (map[y][x - 1] == ' ' || map[y][x + 1] == ' '
					|| map[y - 1][x] == ' ' || map[y + 1][x] == ' ')
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

	(1) && (i = -1, len = 0, tmp = 0);
	while (cub->map[++i])
	{
		tmp = len;
		len = ft_strlen(cub->map[i]);
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
	(1) && (cub->height = len, cub->width = ft_strlen2d(cub->map));
}

void	parse_it(char *s, t_data *cub)
{
	store_instructions(s, cub);
	store_map(cub);
	get_map_ready(cub);
	check_elements(cub);
	check_walls(cub->map, cub);
	check_space(cub->map, cub);
	close(cub->fd);
}
