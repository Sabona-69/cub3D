/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-omra <hel-omra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:21:34 by hel-omra          #+#    #+#             */
/*   Updated: 2024/08/22 04:28:39 by hel-omra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	space_av;
	size_t	i;
	size_t	j;

	src_len = ft_strlen(src);
	if (!dst && size == 0)
		return (src_len);
	i = 0;
	j = ft_strlen(dst);
	dst_len = ft_strlen(dst);
	if (size <= dst_len)
		return (size + src_len);
	space_av = size - dst_len;
	while (src[i] && i < space_av - 1)
	{
		dst[j] = src[i];
		i++;
		j++;
	}
	dst[j] = '\0';
	return (dst_len + src_len);
}
