/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr_b.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-omra <hel-omra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:28:44 by hel-omra          #+#    #+#             */
/*   Updated: 2024/11/21 07:19:46 by hel-omra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_b.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	src_len;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	src_len = ft_strlen(s);
	if (start > src_len)
		return (ft_strdup(""));
	if (len > src_len - start)
		len = src_len - start;
	sub = (char *)ft_malloc(len + 1, MALLOC);
	if (!sub)
		return (NULL);
	while (i < len && s[start])
	{
		sub[i] = s[start];
		i++;
		start++;
	}
	sub[i] = '\0';
	return (sub);
}
