/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjack <tjack@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 12:53:37 by tjack             #+#    #+#             */
/*   Updated: 2021/05/13 12:53:38 by tjack            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	handle_closing_quote(t_par *par, const char *data, char *str,
		int quote)
{
	char	c;

	if (quote == 1)
		c = '\'';
	else
		c = '"';
	if (data[par->i] != c)
	{
		ft_putendl_fd(str, 2);
		g_gl.status = 1;
		par->call_prompt = 1;
		return (1);
	}
	if (*par->quote_flag && data[par->i] == c)
		*par->quote_flag = 0;
	par->i++;
	if ((data[par->i] == ' ' && !(*par->quote_flag)) || !data[par->i]
		|| data[par->i] == '|')
	{
		skip_spaces(par, data);
		par->start_append_str = 1;
	}
	return (0);
}

static int	is_special_after_backlash(t_par *par, const char *data)
{
	if (data[par->i + 1] == '$' || data[par->i + 1] == '"'
		|| data[par->i + 1] == '\\')
		return (1);
	return (0);
}

void	parse_double_quotes(t_par *par, const char *data, t_list *environ)
{
	par->i++;
	par->quote2 = 1;
	while (data[par->i] && data[par->i] != '"')
	{
		if (data[par->i] == '\\' && is_special_after_backlash(par, data))
			par->i++;
		else if (data[par->i] == '$' && data[par->i - 1] != '\\')
		{
			parse_env_var(par, data, environ);
			continue ;
		}
		else if (data[par->i] == '"' && data[par->i - 1] == '\\')
			append_char(par, data);
		else if (data[par->i - 1] != '\\' && data[par->i] == '"'
			&& ((data[par->i + 1] == ' ' && !par->quote2) || !data[par->i + 1]))
		{
			par->i++;
			break ;
		}
		append_char(par, data);
	}
	par->quote_flag = &par->quote2;
	if (handle_closing_quote(par, data, "Close double quotes", 2))
		return ;
}

void	parse_single_quotes(t_par *par, const char *data)
{
	par->i++;
	par->quote1 = 1;
	while (data[par->i] != '\'' && data[par->i])
		append_char(par, data);
	par->quote_flag = &par->quote1;
	if (handle_closing_quote(par, data, "Close single quotes", 1))
		return ;
}
