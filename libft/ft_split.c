/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-omra <hel-omra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 01:03:15 by hel-omra          #+#    #+#             */
/*   Updated: 2024/11/03 07:07:39 by hel-omra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(char const *s, char *set)
{
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (ft_strchr(set, s[i]))
			i++;
		if (s[i] != '\0')
			count++;
		while (s[i] && !ft_strchr(set, s[i]))
			i++;
	}
	return (count);
}

static void	ft_free2d(char **str, int k)
{
	while (k--)
		free(str[k]);
	free(str);
}

char	**ft_split(char const *s, char *set)
{
	char	**str;
	int		i;
	int		j;
	int		k;

	if (!s)
		return (NULL);
	str = (char **)malloc((ft_count(s, set) + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	i = 0;
	k = 0;
	while (k < ft_count(s, set))
	{
		while (s[i] && ft_strchr(set, s[i]))
			i++;
		j = i;
		while (s[i] && !ft_strchr(set, s[i]))
			i++;
		str[k] = ft_substr(s, j, i - j);
		if (str[k++] == NULL)
			return (ft_free2d(str, k - 1), NULL);
	}
	str[k] = NULL;
	return (str);
}
