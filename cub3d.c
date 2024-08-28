#include "cub3d.h"

char *get_texture_line(char *s)
{
	char **split;
	char *new;

	split = ft_split(s, " ");
	if (ft_strlen2d(split) != 2)
		(ft_putstr_fd("invalid texture\n", 2), exit(1));
	new = ft_strdup(split[1]);
	// free(s);
	// printf("<%s>\n", new);
	free_it(split, ft_strlen2d(split));
	return (new);
}

void get_colors(int *tab, char *s)
{
	char **split;
	char *tmp;
	int i;
	int j;

	i = -1;
	j = 0;
	if (!ft_isdigit(*s) || !ft_isdigit(s[ft_strlen(s) - 1]))
		(ft_putstr_fd("Invalid Colors1", 2), exit(1));
	while (s[++i])
	{
		if (s[i] == ',')
			j++;
	}
	if (j != 2)
		(ft_putstr_fd("Invalid comma !", 2), exit(1));
	split = ft_split(s, ",");
	if (ft_strlen2d(split) != 3)
		(ft_putstr_fd("set 3 colors\n", 2), exit(1));
	i = -1;
	while (++i < 3)
	{
		tmp = ft_strtrim(split[i], " ");
		tab[i] = my_atoi(tmp);
		free(tmp);
	}
	if (tab[0] == -1 || tab[1] == -1 || tab[2] == -1)
		(ft_putstr_fd("Invalid Colors", 2), exit(1));
	free_it(split, ft_strlen2d(split));
}

void store_map(t_data *cub)
{
	int fd;
	char *tmp;
	char **map;

	map = NULL;
	int i = 100;
	int j = 100;
	int k = 0;

	if (!cub->line)
		return (printf("empty map !\n"), exit(1));
	while (cub->line)
	{
		tmp = cub->line;
		cub->line = ft_strtrim(cub->line, "\n");
		if (!*cub->line || cub->line[skip_char(cub->line, ' ')] == '\0')
		{
			free(cub->line);
			free(tmp);
			cub->line = get_next_line(cub->fd);
		}
		else
			break;
	}
	i = 100;
	while (cub->line)
	{
		tmp = cub->line;
		cub->line = ft_strtrim_end(cub->line, " \n");
		if (i < j)
			j = i;
		if (cub->line[0] == ' ')
			i = skip_char(cub->line, ' ');
		else if (cub->line[0])
			i = 0;
		// if (*(cub->line))`
		map = strjoin2d(map, cub->line);
		free(tmp);
		free(cub->line);
		cub->line = get_next_line(cub->fd);
	}

	// printf("%d\n", j);
	i = -1;
	while (map[++i])
		cub->map = strjoin2d(cub->map, &(map[i][j]));
	free_it(map, ft_strlen2d(map));
	// i = -1;
	// while (cub->map[++i])
	// 	printf("{{%s}}\n", cub->map[i]);
}

void store_instructions(char *s, t_data *cub)
{
	char *line;
	char *tmp;
	int i;

	i = 0;
	cub->fd = open(s, O_RDONLY);
	if (cub->fd == -1)
		return (printf("Invalid map file !\n"), exit(1));
	cub->line = get_next_line(cub->fd);
	while (cub->line)
	{
		if (i == 6)
		{
			free(cub->line);
			free(tmp);
			break;
		}
		tmp = cub->line;
		cub->line = ft_strtrim(cub->line, " \n");
		if (ft_strncmp("NO ", cub->line, 3) == 0)
			(1) && (cub->NO = get_texture_line(cub->line), i++);
		else if (ft_strncmp("SO ", cub->line, 3) == 0)
			(1) && (cub->WE = get_texture_line(cub->line), i++);
		else if (ft_strncmp("WE ", cub->line, 3) == 0)
			(1) && (cub->EA = get_texture_line(cub->line), i++);
		else if (ft_strncmp("EA ", cub->line, 3) == 0)
			(1) && (cub->SO = get_texture_line(cub->line), i++);
		else if (ft_strncmp("F ", cub->line, 2) == 0)
			(get_colors(cub->F, cub->line + 2), i++);
		else if (ft_strncmp("C ", cub->line, 2) == 0)
			(get_colors(cub->C, cub->line + 2), i++);
		else if (i != 6 && *cub->line != '\0' && *cub->line != ' ')
			printf("Invalid ins !\n"), exit(1);
		(free(tmp), tmp = NULL);
		free(cub->line);
		cub->line = get_next_line(cub->fd);
	}
	// close(cub->fd);
	// printf("<<%s>>\n",cub->line);
	if (i != 6 || (cub->C[0] == -1 || cub->F[0] == -1))
		return (printf("Invalid map instructions\n"), exit(1));
	if (!cub->EA)
		return (printf("Please set the east texture !\n"), exit(1));
	else if (!cub->NO)
		return (printf("Please set the north texture !\n"), exit(1));
	else if (!cub->SO)
		return (printf("Please set  the south texture !\n"), exit(1));
	else if (!cub->WE)
		return (printf("Please set  the west texture !\n"), exit(1));
}

void check_elements(t_data *cub)
{
	int x;
	int y;
	int flag;

	y = 0;
	flag = 0;
	while (cub->map[y])
	{
		x = 0;
		while (cub->map[y][x])
		{
			if (cub->map[y][x] != '1' && cub->map[y][x] != '0' && cub->map[y][x] != ' ' && cub->map[y][x] != 'W' && cub->map[y][x] != 'N' && cub->map[y][x] != 'S' && cub->map[y][x] != 'E')
				(ft_putstr_fd("Invalid elements!\n", 2), exit(1));
			if (cub->map[y][x] == 'W' || cub->map[y][x] == 'N' || cub->map[y][x] == 'S' || cub->map[y][x] == 'E' && flag == 0)
				(1) && (cub->Player_postition = cub->map[y][x], flag++);
			if (flag > 1)
				(ft_putstr_fd("Player Position error\n", 2), exit(1));
			x++;
		}
		y++;
	}
}

void check_walls(char **map)
{
	int y_len;
	int x_len;
	int y;
	int x;

	x = skip_char(map[0], ' ');
	while (map[0][x])
		if (map[0][x++] != '1')
			(ft_putstr_fd("map : check walls\n", 2), exit(1));
	y_len = ft_strlen2d(map) - 1;
	x = skip_char(map[y_len], ' ');
	while (map[y_len][x])
		if (map[y_len][x++] != '1')
			(ft_putstr_fd("1map : check walls\n", 2), exit(1));
	y = 1;
	while (map[y])
	{
		x_len = ft_strlen(map[y]) - 1;
		x = skip_char(map[y], ' ');
		if (is_empty(map[y]) == FALSE && (map[y][x] != '1' || map[y][x_len] != '1'))
			(ft_putstr_fd("map : check walls\n", 2), exit(1));
		y++;
	}
}

void check_space(char **map)
{
	int y;
	int x;

	y = 1;
	while (map[y])
	{
		x = 1;
		while (map[y][x])
		{
			// printf("<%c>", map[y][x]);
			if (map[y][x] == '0' || map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'E' || map[y][x] == 'W')
			{
				if (ft_strlen(map[y - 1]) - 1 < x || ft_strlen(map[y + 1]) - 1 < x)
					(ft_putstr_fd("map : floor not covered with wall\n", 2), exit(1));
				if (map[y][x - 1] == ' ' || map[y][x + 1] == ' ' || map[y - 1][x] == ' ' || map[y + 1][x] == ' ')
					(ft_putstr_fd("map : floor not covered with wall\n", 2), exit(1));
			}
			x++;
		}
		y++;
	}
}

// void	check_surrounded(char **map, char c)
// {
// 	int		y;
// 	int		x;

// 	y = 1;
// 	while (map[y])
// 	{
// 		x = 1;
// 		while (map[y][x])
// 		{
// 			// printf("<%c>", map[y][x]);
// 			if (map[y][x] == c) // c = '0'
// 			{
// 				if ((ft_strlen(map[y - 1]) - 1) < x || (ft_strlen(map[y + 1]) - 1 < x))
// 					(ft_putstr_fd("map : floor not covered with wall\n", 2), exit(1));
// 				if (map[y][x - 1] == ' ' || map[y][x + 1] == ' ' ||  map[y - 1][x] == ' '  ||  map[y + 1][x] == ' ')
// 					(ft_putstr_fd("map : floor not covered with wall\n", 2), exit(1));
// 			}
// 			x++;
// 		}
// 		y++;
// 	}
// }

void parse_it(char *s, t_data *cub)
{
	store_instructions(s, cub);
	store_map(cub);
	check_elements(cub);
	check_walls(cub->map);
	check_space(cub->map);
	int i = 0;
	// printf("{{%c}}\n", cub->map[0][ft_strlen(cub->map[0]) - 1]);
	while (cub->map[i])
		printf("{{%s}}\n", cub->map[i++]);
}
// printf("<%s>\n", cub->EA);
// 	printf("<%s>\n", cub->NO);
// 	printf("<%s>\n", cub->SO);
// 	printf("<%s>\n", cub->WE);
// 	printf("%d %d %d \n", cub->C[0], cub->C[1], cub->C[2]);

void f()
{
	system("leaks cub3D");
}

#include <string.h>

int main(int ac, char **av)
{
	t_data *cub;
	// atexit(f);
	if (ac != 2 || ft_strlen(av[1]) < 4 || ft_strcmp(".cub", av[1] + ft_strlen(av[1]) - 4) != 0)
		return (printf("Please Insert \"./cub\" + valid map\n"), 1);
	cub = malloc(sizeof(t_data));
	if (!cub)
		return (ft_putstr_fd("malloc failed ", 2), 1);
	ft_memset(cub, 0, sizeof(t_data));
	(1) && (cub->C[0] = -1, cub->F[0] = -1);
	parse_it(av[1], cub);

	// free_it(cub->map, ft_strlen2d(cub->map));
	// free(cub->EA);
	// free(cub->NO);
	// free(cub->SO);
	// free(cub->WE);
	// free(cub);
	// printf("%d\n", my_atoi(av[1]));
}