/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoat <bgoat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 19:49:01 by bgoat             #+#    #+#             */
/*   Updated: 2021/04/11 19:19:11 by bgoat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*a;
	size_t	s;

	s = ft_strlen(s1) + 1;
	a = ft_calloc(s, sizeof(char));
	if (!(a))
		return (NULL);
	ft_memcpy(a, (char *)s1, s);
	return (a);
}
