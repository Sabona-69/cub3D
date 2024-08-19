#include "cub3d.h"

char	*get_texture_line(char *s)
{
	char	**split;
	char	*new;

	split = ft_split(s, " ");
	if (ft_strlen2d(split) != 2)
		(ft_putstr_fd("invalid texture\n", 2), exit(1));
	new = ft_strdup(split[1]);
	// free(s);
	// printf("<%s>\n", new);
	free_it(split, ft_strlen2d(split));
	return (new);
}

void	get_colors(int *tab, char *s)
{
	char	**split;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!ft_isdigit(*s) || !ft_isdigit(s[ft_strlen(s) - 1]))
		(ft_putstr_fd("Invalid Colors1", 2), exit(1));
	while (s[i])
	{
		if (s[i] == ',')
			j++;
		i++;
	}
	if (j != 2)
		(ft_putstr_fd("Invalid ", 2), exit(1));
	split = ft_split(s, ",");
	i = 0;
	if (ft_strlen2d(split) != 3)
		(ft_putstr_fd("Invalid Colors", 2), exit(1));
	tab[0] = my_atoi(ft_strtrim(split[0], " "));
	tab[1] = my_atoi(ft_strtrim(split[1], " "));
	tab[2] = my_atoi(ft_strtrim(split[2], " "));
	// free(s);
	if (tab[0] == -1|| tab[1] == -1 || tab[2] == -1)
		(ft_putstr_fd("Invalid Colors", 2), exit(1));
	free_it(split, ft_strlen2d(split));
}

void    store_map(t_data *cub)
{
	int		fd;
	char	*line;
	char	*tmp;

	line = get_next_line(cub->fd);
	while (line)
	{
		tmp = line;
		line = ft_strtrim(line, " \n");
		if (*line)
			cub->map = strjoin2d(cub->map, line);
		free(tmp);
		line = get_next_line(cub->fd);

	}
	// int i = 0;
	// while (cub->map[i])
	// printf("{{%s}}\n", cub->map[i++]);

}

void    store_instructions(char *s, t_data *cub)
{
	char	*line;
	char	*tmp;
	int		i;

	i = 0;
	cub->fd = open(s, O_RDONLY);
	if (cub->fd == -1)
		return(printf("Invalid map file !\n"), exit(1));
	line = get_next_line(cub->fd);
	while(line && i < 6)
	{
	// printf("[%s]", line);
		tmp = line;
		line = ft_strtrim(line, " \n");
		if (ft_strncmp("NO ", line, 3) == 0)
			(1) && (cub->NO = get_texture_line(line), i++);
		else if (ft_strncmp("SO ", line, 3) == 0)
			(1) && (cub->WE = get_texture_line(line), i++);
		else if (ft_strncmp("WE ", line, 3) == 0)
			(1) && (cub->EA = get_texture_line(line), i++);
		else if (ft_strncmp("EA ", line, 3) == 0)
			(1) && (cub->SO = get_texture_line(line), i++);
		else if (ft_strncmp("F ", line, 2) == 0)
			(get_colors(cub->F, line + 2), i++);
		else if (ft_strncmp("C ", line, 2) == 0)
			(get_colors(cub->C, line + 2), i++);
		else if (i != 6 && *line != '\0' && *line != ' ')
			printf("Invalid ins !\n"), exit(1);
			(free(tmp), tmp = NULL);
		line = get_next_line(cub->fd);
	}
	// close(cub->fd);
	if (!cub->EA)
		return(printf("Please set the east texture !\n"), exit(1));
	else if (!cub->NO)
		return(printf("Please set the north texture !\n"), exit(1));
	else if (!cub->SO)
		return(printf("Please set  the south texture !\n"), exit(1));
	else if (!cub->WE)
		return(printf("Please set  the west texture !\n"), exit(1));
	else if (cub->C[0] == -1 || cub->F[0] == -1)
		return(printf("Invalid Colors !\n"), exit(1));
	if (i != 6)
		return(printf("Invalid map instructions\n"), exit(1));

}

void		check_walls(char **map)
{
	int		y;
	int		y_len;
	int		x;
	int		x_len;

	y = 0;
	y_len = ft_strlen2d(map) - 2;
	while (map[y])
	{
		x_len = ft_strlen(map[y] - 1);
		if (map[y][x_len] == '\n')
			printf("{{\\n}}\n");
		else if (map[y][x_len] == '\0')
			printf("{{\\0}}\n");
		else 
			printf("{{%c}\n", map[y][x_len]);
			printf("[[%d]]\n", x_len);
		x = 0;
		// printf("=======================================\n");
		// printf("line[%d] => map[%d][%d] == '%c'\n",y + 1, y, x, map[y][x]);
		// printf("line[%d] => x_len = %d || value = '%c'\n",y + 1, x_len, map[y][x_len]);
		// printf("line[%d] => y_len = %d || value = '%c'\n", y + 1, y_len, map[y_len][x]);
		// if (map[0][x] != '1' || map[y_len][x] != '1') 
		// 		(ft_putstr_fd("map : 1check walls\n", 2), exit(1));
		if (map[y][0] != '1' || map[y][x_len] != '1')
				(ft_putstr_fd("map : 2check walls\n", 2), exit(1));
		x++;
		y++;
	}
}


void	parse_it(char *s, t_data *cub)
{
	store_instructions(s, cub);
	store_map(cub);
	check_walls(cub->map);

}
// printf("<%s>\n", cub->EA);
// 	printf("<%s>\n", cub->NO);
// 	printf("<%s>\n", cub->SO);
// 	printf("<%s>\n", cub->WE);
// 	printf("%d %d %d \n", cub->C[0], cub->C[1], cub->C[2]); 
// 	printf("%d %d %d \n", cub->F[0], cub->F[1], cub->F[2]); 

void	f(){
	system("leaks cub3d");
}
#include <string.h>
int main(int ac, char **av)
{
	t_data	*cub;
	// atexit(f);
	if (ac != 2 || ft_strlen(av[1]) < 4 || ft_strcmp(".cub", av[1] + ft_strlen(av[1]) - 4) != 0)
		return(printf("Please Insert \"./cub\" + valid map\n"), 1);
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
	// printf("%d\n", my_atoi(av[1]));
}