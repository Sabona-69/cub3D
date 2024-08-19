#include "cub3d.h"

	char	**strjoin2d (char **str, char *s)
	{
		char **new;
		int		i;

		i = -1;
		if (!s)
			return (str);
		if (!str)
		{
			new = malloc(2 * sizeof(char *));
			return (new[0] = ft_strdup(s), new[1] = NULL, new);
		}
		new = malloc(sizeof(char *) * (ft_strlen2d(str) + 2));
		while (str[++i])
			new[i] = ft_strdup(str[i]);
		new[i++] = ft_strdup(s);
		new[i] = NULL;
		free_it(str, ft_strlen2d(str));
		return (new);
	}

void	free_it(char **str, int i)
{
	while (i--)
		free(str[i]);
	free(str);
}

int	my_atoi(char *str)
{
	int		res;

	res = 0;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (-1);
		res = res * 10 + *str - '0';
		if (res > 255)
			return (-1);
		str++;
	}
	return (res);
}

int	ft_strlen2d(char **s)
{
	int		i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*till_char(char *s, char c)
{
	while (*s && *s == c)
		s++;
	return (s);
}