/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_disjoiner.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjack <tjack@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 12:52:28 by tjack             #+#    #+#             */
/*   Updated: 2021/05/13 13:10:15 by tjack            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	append_str1(t_node **cur)
{
	if (!(*cur)->s)
	{
		(*cur)->s = (char *) realloc((*cur)->s, 1);
		(*cur)->s[0] = '\0';
	}
	(*cur)->data_ar = (char **)realloc((*cur)->data_ar,
			sizeof(char *) * ((*cur)->ar_size + 1));
	(*cur)->data_ar[(*cur)->ar_size - 1] = ft_strdup((*cur)->s);
	(*cur)->data_ar[(*cur)->ar_size] = NULL;
	(*cur)->ar_size++;
	free((*cur)->s);
	(*cur)->s = NULL;
	(*cur)->s_size = 1;
}

static int	append_char1(t_node **cur, char ch)
{
	if (ch && (ch != ';' || (1 && (*cur)->s && (((*cur)->s[(*cur)->s_size - 2]
						&& (*cur)->s[(*cur)->s_size - 2] == '\\')
					|| (*cur)->quote1 || (*cur)->quote2))))
	{
		(*cur)->s = (char *)realloc((*cur)->s,
				sizeof(char) * ((*cur)->s_size + 1));
		(*cur)->s[(*cur)->s_size - 1] = ch;
		(*cur)->s[(*cur)->s_size] = '\0';
		(*cur)->s_size++;
		return (0);
	}
	else if (!ch || (1 && (*cur)->s && (*cur)->s[(*cur)->s_size - 2]
			&& (*cur)->s[(*cur)->s_size - 2] != '\\'
			&& !(*cur)->quote1 && !(*cur)->quote2))
		return (1);
	return (0);
}

static void	is_quote(t_node **cur, char ch)
{
	if (ch == '\'' && (*cur)->s && (*cur)->s[(*cur)->s_size - 2]
		&& (*cur)->s[(*cur)->s_size - 2] != '\\' && (*cur)->quote1)
		(*cur)->quote1 = 0;
	else if (ch == '"' && (*cur)->s && (*cur)->s[(*cur)->s_size - 2]
		&& (*cur)->s[(*cur)->s_size - 2] != '\\' && (*cur)->quote2)
		(*cur)->quote2 = 0;
	else
	{
		if (ch == '\'')
			(*cur)->quote1 = 1;
		else if (ch == '"')
			(*cur)->quote2 = 1;
	}
}

static int	check_line(const char *s)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i] == ' ')
			i++;
		if (!s[i])
			return (1);
		return (0);
	}
	else
		return (1);
}

int	disjoin_data(t_node **cur)
{
	size_t	i;

	i = 0;
	(*cur)->quote1 = 0;
	(*cur)->quote2 = 0;
	(*cur)->s = NULL;
	(*cur)->s_size = 1;
	(*cur)->data_ar = NULL;
	(*cur)->ar_size = 1;
	while (i <= ft_strlen((*cur)->data))
	{
		is_quote(cur, (*cur)->data[i]);
		if ((check_line((*cur)->s) || (i > 0 && (*cur)->data[i - 1] == '|'))
			&& (*cur)->data[i] == ';')
		{
			print_error(NULL, NULL,
				"syntax error near unexpected token `;'");
			g_gl.status = 258;
			return (1);
		}
		if (append_char1(cur, (*cur)->data[i]))
			append_str1(cur);
		i++;
	}
	return (0);
}
