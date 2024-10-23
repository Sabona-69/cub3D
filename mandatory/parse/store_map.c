#include "../cub3d.h"

void	check_empty_map(t_data *cub)
{
	char	*tmp;

	while (cub->line)
	{
		tmp = ft_strtrim(cub->line, "\n");
		if (!is_empty(tmp))
			break ;
		free(cub->line);
		free(tmp);
		cub->line = get_next_line(cub->fd);
	}
	free(tmp);
	if (!cub->line)
		return (exiting(cub, 1));
}

void	store_map(t_data *cub)
{
	char	*tmp;
	char	**map;
	int		i;
	int		j;

	check_empty_map(cub);
	(1) && (map = NULL, i = ft_strlen(cub->line), j = i);
	while (cub->line)
	{
		(1) && (tmp = cub->line, cub->line = ft_strtrim_end(cub->line, " \n"));
		if (!cub->line[0])
			(free(cub->line), cub->line = ft_strdup(" "));
		if (i < j)
			j = i;
		if (cub->line[0] == ' ')
			i = skip_char(cub->line, ' ');
		else if (cub->line[0])
			i = 0;
		map = strjoin2d(map, cub->line);
		(free(tmp), free(cub->line), cub->line = get_next_line(cub->fd));
	}
	(free(cub->line), i = -1);
	while (map[++i])
		cub->map = strjoin2d(cub->map, &(map[i][j]));
	free2d(map, ft_strlen2d(map));
}
