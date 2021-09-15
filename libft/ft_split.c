/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoat <bgoat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 17:19:00 by bgoat             #+#    #+#             */
/*   Updated: 2021/04/11 19:20:51 by bgoat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_lines(const char *s, char c)
{
	int	n_lines;
	int	i;

	i = 0;
	n_lines = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			n_lines++;
		i++;
	}
	return (n_lines);
}

static int	count_letters(const char *s, char c, int j)
{
	int	n_letters;

	n_letters = 0;
	while (s[j] != c && s[j])
	{
		j++;
		n_letters++;
	}
	return (n_letters);
}

static char	**free_ptr(char **ptr, int i)
{
	while (i-- > 0)
	{
		free(ptr[i]);
		ptr++;
	}
	free(ptr);
	return (NULL);
}

static char	**fill_arr(char **arr, const char *s, char c, int n_lines)
{
	int	n_letters;
	int	j;
	int	i;

	j = 0;
	i = 0;
	n_letters = 0;
	while (i < n_lines)
	{
		while (s[j] == c && s[j])
			j++;
		n_letters = count_letters(s, c, j);
		if (n_letters != 0)
		{
			arr[i] = ft_substr(s, j, n_letters);
			if (!(arr[i]))
				return (free_ptr(arr, i));
			j = j + n_letters;
			n_letters = 0;
		}
		i++;
	}
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	int		n_lines;
	char	**arr;

	if (!s)
		return (NULL);
	n_lines = count_lines(s, c);
	arr = (char **)ft_calloc(n_lines + 1, sizeof(char *));
	if (!(arr))
		return (NULL);
	else
		fill_arr(arr, s, c, n_lines + 1);
	return (arr);
}
