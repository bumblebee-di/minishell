/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoat <bgoat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 19:37:58 by bgoat             #+#    #+#             */
/*   Updated: 2021/05/11 18:33:46 by bgoat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <dirent.h>

static void	go_home(t_list *environ, char *old)
{
	char	*ptr;

	while (environ)
	{
		if (ft_strncmp(environ->content, "HOME=", 5) == 0)
		{
			ptr = ft_substr(environ->content, 5, \
				ft_strlen(environ->content));
			chdir(ptr);
			write_oldnew_pwd(old, environ);
			g_gl.status = 0;
			free(ptr);
			return ;
		}
		environ = environ->next;
	}
	ft_putendl_fd("binara11: cd: HOME not set", STDERR_FILENO);
	g_gl.status = 1;
}

/*
**	@brief	rewrites relative part of path if it exist
**
**	@param	tmp		old
**	@param	ptr		new path (absolute)
**	@param	newpath		new path (relative part)
**	@param	environ		environment variables
*/

static void	relative_path(char *ptr, char *newpath, t_list *environ)
{
	char	*tmp;

	tmp = ft_strdup(ptr);
	ft_strlcat(ptr, "/", ft_strlen(ptr) + 2);
	ft_strlcat(ptr, newpath, ft_strlen(ptr) + ft_strlen(newpath) + 2);
	if (chdir(ptr) == 0)
		write_oldnew_pwd(tmp, environ);
	else
	{
		print_error("cd", newpath, strerror(errno));
		g_gl.status = 1;
	}
	free(tmp);
}

/*
**	@brief	realisation of cd command
**
**	@param	newpath		path (relative/absolute)
**	@param	environ		environment variables
*/

void	builtin_cd(char *newpath, t_list *environ)
{
	char	*ptr;
	char	*tmp;

	ptr = malloc(255);
	if (validate_cd(ptr, newpath) == 0)
		return ;
	if (getcwd(ptr, 255) == NULL)
		ft_putendl_fd("binara11: cd: getcwd failed", STDERR_FILENO);
	tmp = ft_strdup(ptr);
	if (!newpath)
		go_home(environ, ptr);
	else if (newpath[0] == '/')
	{
		if (chdir(newpath) == 0)
			write_oldnew_pwd(tmp, environ);
		else
		{
			print_error("cd", newpath, strerror(errno));
			g_gl.status = 1;
		}
	}
	else
		relative_path(ptr, newpath, environ);
	free(tmp);
	free(ptr);
}
