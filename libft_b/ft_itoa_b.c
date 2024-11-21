/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-omra <hel-omra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:48:28 by hel-omra          #+#    #+#             */
/*   Updated: 2024/11/21 07:19:46 by hel-omra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_b.h"

static int	n_len(int n)
{
	int	i;

	i = 0;
	if (n < 0)
		i++;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static char	*ft_print(char *itoaa, int len, int n, int i)
{
	while (len - 1 >= i)
	{
		itoaa[len - 1] = (n % 10) + 48;
		n /= 10;
		len--;
	}
	return (itoaa);
}

char	*ft_itoa(int n)
{
	char		*itoaa;
	int			len;
	int			i;

	i = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	len = n_len(n);
	itoaa = (char *)ft_malloc(len + 1, MALLOC);
	if (!itoaa)
		return (NULL);
	if (n < 0)
	{
		n = -n;
		itoaa[0] = '-';
		i = 1;
	}
	itoaa[len] = '\0';
	return (ft_print(itoaa, len, n, i));
}
