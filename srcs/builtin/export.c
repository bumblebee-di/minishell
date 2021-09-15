/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoat <bgoat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 15:01:42 by bgoat             #+#    #+#             */
/*   Updated: 2021/05/12 18:08:23 by bgoat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
**	@brief	initiate xport structure
**
**	@param	export		struct itself
*/

static void	init_export(t_export *export)
{
	export->eq = 0;
	export->plus = 0;
	export->var = NULL;
	export->value = NULL;
}

/*
**	@brief	checks if 
**
**	@param	arg		argument to validate
**	@param	export		export struct
*/

int	valid_str(char *arg, int i, t_export *export)
{
	if (isalpha(arg[i]) || arg[i] == '_')
		return (1);
	if (arg[i] == '+' && arg[i + 1] == '=' && i > 0)
	{
		export->plus = i;
		return (1);
	}
	if (arg[i] == '=' && i > 0)
		return (1);
	print_error("export", arg, "not a valid identifier");
	return (0);
}

static int	validate_export_structure(char *arg, t_export *export)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (export->eq == 0 && !valid_str(arg, i, export))
			return (0);
		else if (arg[i] == '=' && export->eq == 0)
		{
			export->eq = i;
			if (export->plus > 0)
				export->var = ft_substr(arg, 0, export->plus);
			else
				export->var = ft_substr(arg, 0, i);
		}
		i++;
	}
	return (1);
}

/*
**	@brief	fill export structure (variable name + it's value (if exist))
**	then it calls overwite_env function to owervrite value of variable
**	or to add var
**
**	@param	export		param with var and value
**	@param	arg		strig to write in env 
**	@param	environ		list of env variable
*/

static void	fill_export(t_export *export, char *arg, t_list **environ)
{
	int	i;

	i = ft_strlen(arg);
	if (export->eq != 0)
		export->value = ft_substr(arg, export->eq + 1, i - export->eq + 1);
	else
	{
		export->eq = i;
		export->var = ft_strdup(arg);
	}
	if (export->eq != 0 && export->plus == 0 && *environ != NULL)
	{
		overwrite_env(*environ, export, arg);
		g_gl.status = 0;
	}
	else if (export->eq != 0 && export->plus != 0 && *environ != NULL)
	{
		append_env(*environ, export, arg);
		g_gl.status = 0;
	}
}

/*
**	@brief	realisation of export cmd
**
**	@param	lcmd		list of structure with args
**	@param	environ		list of environment variables
*/

void	builtin_export(t_lcmd *lcmd, t_list **environ, int fd)
{
	t_export	export;
	int			i;
	int			valid;

	i = 1;
	if (!lcmd->arg[1])
	{
		sort_print_env(*environ, fd);
		g_gl.status = 0;
		return ;
	}
	while (lcmd->arg[i] != NULL)
	{
		init_export(&export);
		valid = validate_export_structure(lcmd->arg[i], &export);
		if (valid == 1)
			fill_export(&export, lcmd->arg[i], environ);
		free(export.var);
		free(export.value);
		if (*environ == NULL)
			return ;
		i++;
	}
}
