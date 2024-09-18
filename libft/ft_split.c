/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-omra <hel-omra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 01:03:15 by hel-omra          #+#    #+#             */
/*   Updated: 2024/09/18 20:29:02 by hel-omra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *str, char *charset)
{
	int		count;
	size_t	i;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (ft_strchr(charset, str[i]) && str[i])
			i++;
		if (str[i])
			count++;
		while (!ft_strchr(charset, str[i]) && str[i])
			i++;
	}
	return (count);
}

static char	*ft_allocate(const char *str, char *charset, int *i)
{
	int		size;
	int		n;
	char	*word;

	size = 0;
	n = 0;
	if (!str)
		return (NULL);
	while (str[*i] && ft_strchr(charset, str[*i]))
		(*i)++;
	while (str[*i] && !ft_strchr(charset, str[*i]))
	{
		(*i)++;
		size++;
	}
	word = (char *)ft_calloc(1, size + 1);
	while (n < size && *str)
	{
		word[n] = str[(*i) - size + n];
		n++;
	}
	word[n] = 0;
	return (word);
}

static void	free2d(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char	**ft_split(const char *str, char *charset)
{
	int		i;
	int		c_words;
	char	**ret;
	int		n;

	if (!str)
		return ((char **)ft_strdup(""));
	c_words = count_words(str, charset);
	ret = (char **)ft_calloc(sizeof(char *), (c_words + 1));
	i = 0;
	n = 0;
	while (n < c_words && *str)
	{
		ret[n] = ft_allocate(str, charset, &i);
		if (!ret[n])
		{
			free2d(ret);
			return (NULL);
		}
		n++;
	}
	ret[n] = 0;
	return (ret);
}