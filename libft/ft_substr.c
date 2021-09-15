/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoat <bgoat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 09:46:45 by bgoat             #+#    #+#             */
/*   Updated: 2021/05/05 13:50:06 by bgoat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;

	if (s == 0)
		return (NULL);
	substr = ft_calloc(len + 1, sizeof(char));
	if (!(substr))
		return (NULL);
	if (start >= ft_strlen(s))
		return (substr);
	ft_strlcpy(substr, (s + start), len + 1);
	return (substr);
}
