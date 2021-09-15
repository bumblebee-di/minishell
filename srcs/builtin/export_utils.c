/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoat <bgoat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 15:01:42 by bgoat             #+#    #+#             */
/*   Updated: 2021/05/13 12:40:30 by bgoat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	append_new_env(t_list *environ, t_export *export, char *arg)
{
	char	*tmp;

	free(export->value);
	export->value = ft_strdup(&arg[export->eq]);
	tmp = ft_strjoin(export->var, export->value);
	ft_lstadd_back(&environ, ft_lstnew(ft_strdup(tmp)));
	free(tmp);
}

static void	append_to_env(t_list *environ, t_export *export, char *arg)
{
	char	*tmp;

	tmp = environ->content;
	if (export->value[0] == '\0')
		return ;
	free(export->value);
	export->value = ft_strdup(&arg[export->eq]);
	if (ft_strncmp(environ->content, export->var, export->plus + 1) == 0)
		environ->content = ft_strjoin(tmp, export->value);
	else
		environ->content = ft_strjoin(tmp, export->value + 1);
	free(tmp);
}

void	append_env(t_list *environ, t_export *export, char *arg)
{
	while (environ != NULL)
	{
		if (ft_strncmp(environ->content, export->var, export->plus) == 0)
		{
			append_to_env(environ, export, arg);
			break ;
		}
		if (environ->next != NULL)
			environ = environ->next;
		else
		{
			append_new_env(environ, export, arg);
			break ;
		}
	}
}

/*
**	@brief	overwrite value of the var, or create new var
**
**	@param	environ		list of environment variables
**	@param	export		export structure with var name, and value
**	@param	arg		name+value for new var
*/

void	overwrite_env(t_list *environ, t_export *export, char *arg)
{
	while (environ != NULL)
	{
		if (ft_strncmp(environ->content, export->var, export->eq) == 0)
		{
			free(environ->content);
			environ->content = ft_strdup(arg);
			break ;
		}
		if (environ->next != NULL)
			environ = environ->next;
		else
		{
			ft_lstadd_back(&environ, ft_lstnew(ft_strdup(arg)));
			break ;
		}
	}
}
