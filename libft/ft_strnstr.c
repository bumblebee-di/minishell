/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoat <bgoat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 13:05:51 by bgoat             #+#    #+#             */
/*   Updated: 2021/04/11 19:17:51 by bgoat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hayastack, const char *needle, size_t len)
{
	size_t	n;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	n = ft_strlen(needle);
	if (!(n))
		return ((char *)hayastack);
	while (*(hayastack + i) != '\0' && i <= len - n)
	{
		j = 0;
		while (*(needle + j) && j < len && \
			*(needle + j) == *(hayastack + i + j))
			j++;
		if (j == n && *(needle + j) == '\0')
			return ((char *)(hayastack + i));
		i++;
	}
	return (NULL);
}
