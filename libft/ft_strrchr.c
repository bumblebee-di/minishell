/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoat <bgoat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 12:11:46 by bgoat             #+#    #+#             */
/*   Updated: 2020/11/11 13:07:31 by bgoat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*begin;
	char	*end;
	size_t	i;
	size_t	n;

	begin = (char *)s;
	end = NULL;
	i = 0;
	n = ft_strlen(s);
	while (i < n + 1)
	{
		if (*begin == (char)c)
			end = begin;
		begin++;
		i++;
	}
	return (end);
}
