/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjack <tjack@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 12:53:21 by tjack             #+#    #+#             */
/*   Updated: 2021/05/13 12:53:23 by tjack            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	skip_spaces(t_par *par, const char *data)
{
	while (data && data[par->i])
	{
		if (data[par->i] != ' ')
			return ;
		if (data[par->i] == ' ')
			par->i++;
	}
}

void	par_init(t_par *par)
{
	par->s = NULL;
	par->s_size = 1;
	par->arg = NULL;
	par->arg_size = 1;
	par->env_name = NULL;
	par->env_size = 0;
	par->ri = NULL;
	par->ro = NULL;
	par->aro = NULL;
	par->quote1 = 0;
	par->quote2 = 0;
	par->i = 0;
	par->start_append_str = 0;
	par->call_prompt = 0;
	par->filename = NULL;
	par->quote_flag = NULL;
}

int	check_final_backslash(t_dlist **ddl)
{
	if ((*ddl)->tail->data && (*ddl)->tail->data[(*ddl)->tail->data_size - 2]
		&& (*ddl)->tail->data[(*ddl)->tail->data_size - 2] == '\\')
	{
		ft_putendl_fd("No multiline", 2);
		add_back(ddl);
		return (1);
	}
	return (0);
}
