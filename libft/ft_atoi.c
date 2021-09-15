/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoat <bgoat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 13:32:11 by bgoat             #+#    #+#             */
/*   Updated: 2021/04/11 19:26:37 by bgoat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int			znak;
	long int	digit;

	znak = 1;
	digit = 0;
	while (((*str == ' ' || *str == '\n' || *str == '\v' || *str == '\f' \
		|| *str == '\r' || *str == '\t')) && *str != '\0')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			znak = -1;
		str++;
	}
	while (*str != '\0' && ft_isdigit(*str))
	{
		digit = (digit * 10) + (*str - '0');
		str++;
	}
	return (znak * digit);
}
