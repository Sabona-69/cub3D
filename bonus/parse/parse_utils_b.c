#include "../../include/cub3d_b.h"

int	is_empty(char *s)
{
	while (*s && (*s == ' ' || *s == '\n'))
		s++;
	if (*s)
		return (FALSE);
	return (TRUE);
}

char *ft_strtrim_end(char const *s1, char const *set)
{
	size_t j;
	char *p;

	if (s1 == NULL || set == NULL)
		return (NULL);
	j = ft_strlen(s1);
	while (j && ft_strchr(set, s1[j]))
		j--;
	if (j == 0)
		p = ft_substr(s1, 0, ft_strlen(s1) - 1);
	else
		p = ft_substr(s1, 0, j + 1);
	if (!p)
		return (NULL);
	return (p);
}

char	**strjoin2d(char **str, char *s)
{
	char	**new;
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
	free2d(str, ft_strlen2d(str));
	return (new);
}

void	free2d(char **str, int i)
{
	while (i--)
		free(str[i]);
	free(str);
}

int	my_atoi(char *str)
{
	int	res;

	res = 0;
	if (!*str)
		return (-1);
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
	int i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

int skip_char(char *s, char c)
{
	int i;

	i = 0;
	while (s[i] && s[i] == c)
		i++;
	return (i);
}