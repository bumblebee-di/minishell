/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoat <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 10:34:10 by bgoat             #+#    #+#             */
/*   Updated: 2020/11/02 11:52:57 by bgoat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	ch;
	char			*ptr;

	ptr = b;
	ch = (unsigned char)c;
	i = 0;
	while (i < len)
	{
		*(ptr + i) = ch;
		i++;
	}
	return (b);
}
