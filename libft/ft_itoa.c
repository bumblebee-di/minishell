/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjack <tjack@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 14:09:22 by tjack             #+#    #+#             */
/*   Updated: 2020/11/12 15:09:17 by tjack            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	count_len(int n)
{
	int	count;

	count = 0;
	while (n / 10 != 0)
	{
		count++;
		n /= 10;
	}
	if (n < 0)
		return (count + 2);
	return (count + 1);
}

static	char	*conv_pos_num(int n, char *ptr, int last_digit)
{
	while (last_digit > -1)
	{
		ptr[last_digit] = n % 10 + '0';
		last_digit--;
		n /= 10;
	}
	return (ptr);
}

static	char	*conv_neg_num(int n, char *ptr, int last_digit)
{
	if (n == -2147483648)
	{
		ft_strlcpy(ptr, "-2147483648", 12);
		return (ptr);
	}
	ptr[0] = '-';
	n = -n;
	while (last_digit > 0)
	{
		ptr[last_digit] = n % 10 + '0';
		last_digit--;
		n /= 10;
	}
	return (ptr);
}

char	*ft_itoa(int n)
{
	char	*ptr;
	int		len;

	len = count_len(n) + 1;
	ptr = (char *)malloc(sizeof(char) * len);
	if (ptr == NULL)
		return (NULL);
	ptr[len - 1] = '\0';
	len = len - 2;
	if (n >= 0)
		return (conv_pos_num(n, ptr, len));
	else
		return (conv_neg_num(n, ptr, len));
}
