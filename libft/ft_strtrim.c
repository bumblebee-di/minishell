/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoat <bgoat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 10:51:46 by bgoat             #+#    #+#             */
/*   Updated: 2020/11/11 13:08:00 by bgoat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	begin;
	size_t	end;

	begin = 0;
	if (!s1)
		return (NULL);
	end = ft_strlen(s1);
	while (s1[begin] && ft_strchr(set, s1[begin]))
		begin++;
	if (begin == end)
		return (ft_substr("", begin, 1));
	while (ft_strchr(set, s1[end]) && s1[--end])
	{
	}
	return (ft_substr(s1, begin, end - begin + 1));
}
