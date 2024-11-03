/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-omra <hel-omra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:21:09 by hel-omra          #+#    #+#             */
/*   Updated: 2024/11/03 02:35:01 by hel-omra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*s;
	size_t	bytes;

	if (count == 0 || size == 0)
	{
		s = malloc(0);
		if (!s)
			return (NULL);
		return (s);
	}
	bytes = count * size;
	if (bytes / size != count)
		return (NULL);
	s = malloc(bytes);
	if (!s)
		(ft_putstr_fd("malloc failed", 2), exit(1));
	ft_bzero(s, bytes);
	return (s);
}
