/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoat <bgoat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 11:10:19 by bgoat             #+#    #+#             */
/*   Updated: 2020/11/08 14:06:59 by bgoat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	t;
	size_t	s;

	if (!dst)
		return (0);
	t = ft_strlen(src);
	if (dstsize == 0)
		return (t);
	s = dstsize - 1;
	while (s-- && *src)
		*dst++ = *src++;
	*dst = '\0';
	return (t);
}
