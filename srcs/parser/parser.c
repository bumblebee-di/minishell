/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjack <tjack@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 12:53:28 by tjack             #+#    #+#             */
/*   Updated: 2021/05/13 12:53:30 by tjack            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_pipe(t_par *par, const char *data)
{
	par->i++;
	skip_spaces(par, data);
	set_redir_and_clean_prev_filename(par, NULL, 0);
	if (!data[par->i] || (!par->s && !par->ri && !par->ro && !par->aro))
	{
		ft_putendl_fd("binara11: syntax error", 2);
		g_gl.status = 258;
		par->call_prompt = 1;
	}
}

static void	check_options(t_par *par, const char *data, t_list *environ)
{
	if (data[par->i] && data[par->i] == '\'')
		parse_single_quotes(par, data);
	else if (data[par->i] && data[par->i] == '\"')
		parse_double_quotes(par, data, environ);
	else if (data[par->i] && (data[par->i] == '>' || data[par->i] == '<'))
		parse_files(par, data);
	else if (data[par->i] == '$')
		parse_env_var(par, data, environ);
	else if (data[par->i] == '\\')
	{
		par->i++;
		append_char(par, data);
	}
	else if (data[par->i] && (data[par->i] != ' ' || (data[par->i] == ' '
				&& data[par->i - 1] == '\\')) && data[par->i] != '\''
		&& data[par->i] != '"' && data[par->i] != '|')
		append_char(par, data);
	else if (data[par->i] == '|' && !par->arg)
		handle_pipe(par, data);
}

static void	get_args(t_lcmd **lcmd, t_par *par, const char *data,
	t_list *environ)
{
	while (data[par->i])
	{
		check_options(par, data, environ);
		if (par->call_prompt)
		{
			free_array(par->arg);
			return ;
		}
		if (par->start_append_str)
			append_str(par, data);
		if (par->arg && (!data[par->i]
				|| data[par->i] == '|'))
			append_lcmd(lcmd, par, data);
	}
}

int	parser(t_lcmd **lcmd, const char *data, t_list *environ)
{
	t_par	par;

	par_init(&par);
	skip_spaces(&par, data);
	get_args(lcmd, &par, data, environ);
	set_redir_and_clean_prev_filename(&par, NULL, 0);
	if (par.s)
		free(par.s);
	if (par.call_prompt)
		return (1);
	return (0);
}
