/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove_b.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-omra <hel-omra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 15:24:22 by hel-omra          #+#    #+#             */
/*   Updated: 2024/11/21 07:19:46 by hel-omra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_b.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*d;
	char	*s;

	d = (char *)dst;
	s = (char *)src;
	if (!dst && !src)
		return (NULL);
	if (s == d)
		return (dst);
	if (s > d)
		return (ft_memcpy(dst, src, len));
	else
	{
		while (len--)
			d[len] = s[len];
	}
	return (d);
}