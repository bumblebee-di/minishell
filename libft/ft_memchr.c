/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoat <bgoat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 12:38:13 by bgoat             #+#    #+#             */
/*   Updated: 2020/11/12 13:57:22 by bgoat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*found;
	size_t			i;

	found = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (*(found + i) == (unsigned char)c)
			return (found + i);
		i++;
	}
	return (NULL);
}
