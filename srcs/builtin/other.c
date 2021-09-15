/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoat <bgoat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 15:16:51 by bgoat             #+#    #+#             */
/*   Updated: 2021/05/12 15:10:22 by bgoat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/termcap.h"

/*
**	@brief	implementation of pwd command
*/

void	builtin_pwd(int fd)
{
	char	*ptr;

	ptr = NULL;
	ptr = malloc(255);
	if (getcwd(ptr, 255) == NULL)
		ft_putendl_fd("binara11: pwd: getcwd failed", STDERR_FILENO);
	ft_putendl_fd(ptr, fd);
	free(ptr);
	g_gl.status = 0;
}

/*
**	@brief	implementation of env command
**
**	@param	environ		list of environment variables
**	@param	arg		array with command nam
*/

void	builtin_env(t_list *environ, char *arg, int fd)
{
	int	i;

	i = 0;
	if (!environ)
		ft_putendl_fd("binara11: env: no env", 2);
	if (!arg)
	{
		while (environ != NULL)
		{
			if (ft_strchr(environ->content, '=') != NULL)
				ft_putendl_fd(environ->content, fd);
			environ = environ->next;
		}
		g_gl.status = 0;
	}
	else
	{
		g_gl.status = 127;
		print_error("env", arg, "no such file or directory");
	}
}

static void	search_for_status(t_lcmd *lcmd)
{
	int		i;
	int		len;

	i = 1;
	while (lcmd->arg[i])
	{
		len = ft_strlen(lcmd->arg[i]);
		if (ft_strnstr(lcmd->arg[i], "$?", len) != NULL)
		{
			free(lcmd->arg[i]);
			lcmd->arg[i] = ft_itoa(g_gl.status);
		}
		i++;
	}
}

/*
**	@brief	checks if programm must use cmd that are builtin or implementation
**
**	@param	lcmd		list of structure with args
**	@param	environ		list of environment variables
**	@return	int		0, if prog should use builtin
*/

int	check_for_builtin(t_lcmd *lcmd, t_list **environ, int fd, t_dlist *ddl)
{
	if (ft_strncmp(lcmd->arg[0], "pwd", 4) == 0)
		builtin_pwd(fd);
	else if (ft_strncmp(lcmd->arg[0], "echo", 5) == 0)
		builtin_echo(lcmd, fd);
	else if (ft_strncmp(lcmd->arg[0], "exit", 5) == 0)
		builtin_exit(lcmd, fd, ddl);
	else if (ft_strncmp(lcmd->arg[0], "env", 4) == 0)
		builtin_env(*environ, lcmd->arg[1], fd);
	else if (ft_strncmp(lcmd->arg[0], "cd", 3) == 0)
		builtin_cd(lcmd->arg[1], *environ);
	else if (ft_strncmp(lcmd->arg[0], "export", 7) == 0)
		builtin_export(lcmd, environ, fd);
	else if (ft_strncmp(lcmd->arg[0], "unset", 6) == 0)
		builtin_unset(lcmd, environ);
	else
	{
		search_for_status(lcmd);
		return (0);
	}
	return (1);
}
