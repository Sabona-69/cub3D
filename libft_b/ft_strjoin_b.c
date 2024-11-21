/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_b.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-omra <hel-omra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:36:31 by hel-omra          #+#    #+#             */
/*   Updated: 2024/11/21 07:19:46 by hel-omra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_b.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*p;

	if (!s1 && !s2)
		return (NULL);
	if (s1 && !s2)
		return (ft_strdup(s1));
	if (!s1 && s2)
		return (ft_strdup(s2));
	p = (char *)ft_malloc((ft_strlen(s1) + ft_strlen (s2)) + 1, MALLOC);
	ft_memcpy(p, s1, ft_strlen(s1));
	ft_memcpy (p + ft_strlen(s1), s2, ft_strlen(s2));
	p[ft_strlen(s2) + ft_strlen(s1)] = '\0';
	return (p);
}
