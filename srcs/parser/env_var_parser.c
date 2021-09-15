/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjack <tjack@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 12:52:52 by tjack             #+#    #+#             */
/*   Updated: 2021/05/13 12:52:53 by tjack            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_env_value_in_2quotes(t_par *par)
{
	char	*temp_str;

	if (!par->quote2)
	{
		temp_str = par->s;
		par->s = ft_strtrim(par->s, " ");
		free(temp_str);
	}
}

static void	append_env_value(t_par *par, const char *data, t_list *temp, int l)
{
	par->some_flag = 0;
	while (((char *)temp->content)[l])
	{
		if (!par->quote2)
		{
			if (((char *) temp->content)[l - 1] &&
				((char *) temp->content)[l - 1] != ' '
				&& ((char *) temp->content)[l] == ' ')
				par->some_flag = 1;
			while (((char *) temp->content)[l] == ' ')
				l++;
			if (((char *) temp->content)[l] != ' ')
				append_env_value_char(par, ((char *) temp->content)[l], data);
		}
		else
			append_env_value_char(par, ((char *) temp->content)[l], data);
		l++;
	}
}

static void	append_env_name_env_value(t_par *par, const char *data,
		t_list *temp, int l)
{
	while (data[par->i] && data[par->i] != '$' && data[par->i] != '"'
		&& data[par->i] != ' ' && data[par->i] != '\\' && data[par->i] != '?'
		&& data[par->i] != '\'' && data[par->i] != '/' && data[par->i] != '=')
		append_env_name_char(par, data);
	while (temp && par->env_name)
	{
		l = 0;
		while (((char *)temp->content)[l] == par->env_name[l])
			l++;
		if (!par->env_name[l] && ((char *)temp->content)[l++] == '=')
		{
			append_env_value(par, data, temp, l);
			break ;
		}
		temp = temp->next;
	}
	while (data[par->i] == '/')
	{
		append_env_value_char(par, data[par->i], data);
		par->i++;
	}
	handle_env_value_in_2quotes(par);
}

static	int	handle_dol_dol_quest_dol_num(t_par *par, const char *data)
{
	if (data[par->i] == '$' && (!data[par->i + 1] || data[par->i + 1] == ' '))
	{
		append_char(par, data);
		par->start_append_str = 1;
		return (1);
	}
	else if (data[par->i] == '$' && data[par->i + 1] == '?')
	{
		append_char(par, data);
		append_char(par, data);
		return (1);
	}
	if (data[par->i] == '$' && !ft_isdigit(data[par->i + 1])
		&& !ft_isalpha(data[par->i + 1]) && data[par->i + 1] != '_')
	{
		append_char(par, data);
		return (1);
	}
	while (data[par->i] == '$')
		par->i++;
	if (ft_isdigit(data[par->i]))
		return (par->i++);
	return (0);
}

void	parse_env_var(t_par *par, const char *data, t_list *environ)
{
	t_list	*temp;
	int		l;

	temp = environ;
	l = 0;
	if (handle_dol_dol_quest_dol_num(par, data))
		return ;
	append_env_name_env_value(par, data, temp, l);
	if (par->env_name)
	{
		free(par->env_name);
		par->env_name = NULL;
		par->env_size = 0;
	}
	if ((data[par->i] == ' ' && !par->quote2) || !data[par->i]
		|| data[par->i] == '|')
	{
		skip_spaces(par, data);
		par->start_append_str = 1;
	}
	if (!par->s)
		par->start_append_str = 0;
}
