/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   appender.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjack <tjack@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 12:52:46 by tjack             #+#    #+#             */
/*   Updated: 2021/05/13 12:52:49 by tjack            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	append_env_name_char(t_par *par, const char *data)
{
	par->env_name = (char *)realloc(par->env_name, sizeof(char)
			* par->env_size + 1);
	par->env_name[par->env_size++] = data[par->i++];
	par->env_name[par->env_size] = '\0';
}

void	append_env_value_char(t_par *par, char ch, const char *data)
{
	if (par->some_flag)
	{
		par->s = (char *) realloc(par->s, sizeof(char) * (par->s_size + 1));
		par->s[par->s_size - 1] = ' ';
		par->s[par->s_size] = '\0';
		par->s_size++;
		par->some_flag = 0;
	}
	par->s = (char *) realloc(par->s, sizeof(char) * (par->s_size + 1));
	par->s[par->s_size - 1] = ch;
	par->s[par->s_size] = '\0';
	par->s_size++;
	par->some_flag = 0;
	if ((data[par->i] == ' ' && !par->quote2) || !data[par->i]
		|| data[par->i] == '|')
	{
		skip_spaces(par, data);
		par->start_append_str = 1;
	}
}

void	append_lcmd(t_lcmd **lcmd, t_par *par, const char *data)
{
	if (data[par->i] == '|' && !data[par->i + 1])
	{
		ft_putendl_fd("No multiline por favor", 1);
		par->call_prompt = 1;
		return ;
	}
	ft_lcmdadd_back(lcmd, ft_lcmdnew(par));
	free_array(par->arg);
	par->arg = NULL;
	par->arg_size = 1;
	if (data[par->i] == '|')
	{
		par->i++;
	}
	skip_spaces(par, data);
}

void	append_str(t_par *par, const char *data)
{
	if (!par->s)
	{
		par->s = (char *) realloc(par->s, 1);
		par->s[0] = '\0';
	}
	par->arg = (char **)realloc(par->arg, sizeof(char *)
			* (par->arg_size + 1));
	par->arg[par->arg_size - 1] = ft_strdup(par->s);
	par->arg[par->arg_size] = NULL;
	par->arg_size++;
	free(par->s);
	par->s = NULL;
	par->s_size = 1;
	par->start_append_str = 0;
	skip_spaces(par, data);
}

void	append_char(t_par *par, const char *data)
{
	par->s = (char *)realloc(par->s, sizeof(char) * (par->s_size + 1));
	par->s[par->s_size - 1] = data[par->i++];
	par->s[par->s_size] = '\0';
	par->s_size++;
	if ((data[par->i] == ' ' && (data[par->i - 1] != '\\'
				|| (data[par->i - 1] == '\\' && data[par->i - 2] == '\\'))
			&& !par->quote2 && !par->quote1) || !data[par->i]
		|| data[par->i] == '|')
	{
		skip_spaces(par, data);
		par->start_append_str = 1;
	}
}
