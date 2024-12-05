#include "../include/cub3d_b.h"

static int	check_nl(char *s)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == '\n')
			return (1);
		s++;
	}
	return (0);
}

static char	*ft_reader(char *s, int fd)
{
	int		rd;
	char	*buffer;
	char	*tmp;

	buffer = ft_malloc((size_t)BUFFER_SIZE + 1, MALLOC);
	if (!buffer)
		return (NULL);
	rd = 1;
	while (rd > 0 && check_nl(s) == 0)
	{
		rd = read(fd, buffer, BUFFER_SIZE);
		if (rd == -1)
			return (NULL);
		buffer[rd] = '\0';
		tmp = s;
		s = ft_strjoin(s, buffer);
	}
	return (s);
}

static char	*ft_output(char *s)
{
	char	*output;
	int		i;

	i = 0;
	if (s[i] == '\0')
		return (NULL);
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		i++;
	output = ft_malloc(i + 1, MALLOC);
	if (!output)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '\n')
	{
		output[i] = s[i];
		i++;
	}
	if (s[i] == '\n')
		output[i++] = '\n';
	output[i] = '\0';
	return (output);
}

static char	*ft_rest(char *s)
{
	char	*rest;
	int		i;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\0')
		return (NULL);
	if (s[i] == '\n')
		i++;
	rest = ft_strdup(&s[i]);
	return (rest);
}

char	*get_next_line(int fd)
{
	static char		*s;
	char			*output;

	if (fd < 0)
		return (NULL);
	s = ft_reader(s, fd);
	if (!s)
		return (NULL);
	output = ft_output(s);
	if (!output)
		return (NULL);
	s = ft_rest(s);
	return (output);
}
