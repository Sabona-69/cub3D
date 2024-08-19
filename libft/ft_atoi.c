/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-omra <hel-omra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 22:32:32 by hel-omra          #+#    #+#             */
/*   Updated: 2024/08/18 02:40:26 by hel-omra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	long		res;

	res = 0;
	while (*str && (*str == 32 || (*str <= 9 && *str >= 13)))
		str++;
	if (*str == '\0')
		return (-1);
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			return (-1);
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + *str - '0';
		str++;
		if (res > 2147483647)
			return (-1);
	}
	while (*str && (*str == 32 || (*str <= 9 && *str >= 13)))
		str++;
	if (*str != '\0' || res == 0)
		return (-1);
	return (res);
}
