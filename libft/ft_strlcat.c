/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoat <bgoat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 17:13:17 by bgoat             #+#    #+#             */
/*   Updated: 2020/11/10 07:29:56 by bgoat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	ss;
	size_t	sd;
	size_t	s;

	ss = ft_strlen(src);
	s = dstsize;
	sd = 0;
	while (*dst && dstsize--)
	{
		sd++;
		dst++;
	}
	dstsize = s - sd;
	if (dstsize-- == 0)
		return (ss + sd);
	while (*src && dstsize--)
	{
		*dst++ = *src++;
	}
	*dst = '\0';
	return (ss + sd);
}
