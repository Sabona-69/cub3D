#include "../cub3d.h"

char	*get_texture_line(char *s, t_data *cub)
{
	char	**split;
	char	*new;
	int		check;

	split = ft_split(s, " ");
	if (ft_strlen2d(split) != 2)
		exiting(cub, 1);
	new = ft_strdup(split[1]);
	check = open(new, O_RDONLY);
	if (check == -1)
		exiting(cub, 1);
	close(check);
	free2d(split, ft_strlen2d(split));
	return (new);
}

void	get_colors(int *tab, char *s, t_data *cub)
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
		exiting(cub, 1);
	split = ft_split(s, ",");
	if (ft_strlen2d(split) != 3)
		exiting(cub, 1);
	i = -1;
	while (++i < 3)
	{
		tmp = ft_strtrim(split[i], " ");
		tab[i] = my_atoi(tmp);
		free(tmp);
	}
	if (tab[0] == -1 || tab[1] == -1 || tab[2] == -1)
		exiting(cub, 1);
	free2d(split, ft_strlen2d(split));
}

int	check_line(t_data *cub, char *tmp)
{
	if (ft_strncmp("NO ", tmp, 3) == 0)
		cub->NO = get_texture_line(tmp, cub);
	else if (ft_strncmp("SO ", tmp, 3) == 0)
		cub->SO = get_texture_line(tmp, cub);
	else if (ft_strncmp("WE ", tmp, 3) == 0)
		cub->WE = get_texture_line(tmp, cub);
	else if (ft_strncmp("EA ", tmp, 3) == 0)
		cub->EA = get_texture_line(tmp, cub);
	else if (ft_strncmp("F ", tmp, 2) == 0)
		get_colors(cub->F, tmp + 2, cub);
	else if (ft_strncmp("C ", tmp, 2) == 0)
		get_colors(cub->C, tmp + 2, cub);
	else
		return (0);
	return (1);
}

void	store_instructions(char *s, t_data *cub)
{
	char	*tmp;
	int		i;

	cub->fd = open(s, O_RDONLY);
	if (cub->fd == -1)
		exiting(cub, 1);
	(1) && (i = 0, cub->line = get_next_line(cub->fd));
	while (cub->line)
	{
		tmp = ft_strtrim(cub->line, " \n");
		if (check_line(cub, tmp))
			i++;
		else if (i != 6 && tmp[0])
			(free(tmp), exiting(cub, 1));
		(free(tmp), free(cub->line));
		cub->line = get_next_line(cub->fd);
		if (i == 6)
			break ;
	}
	if (i != 6 || cub->C[0] == -1 || cub->F[0] == -1 || !cub->EA
		|| !cub->NO || !cub->SO || !cub->WE)
		exiting(cub, 1);
}
