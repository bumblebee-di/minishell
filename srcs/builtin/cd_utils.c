/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoat <bgoat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 14:20:42 by bgoat             #+#    #+#             */
/*   Updated: 2021/05/11 18:50:12 by bgoat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <dirent.h>

static int	rewrite_pwd(t_list *environ, char *path)
{
	if (ft_strncmp(environ->content, "PWD=", 4) == 0)
	{
		free(environ->content);
		environ->content = ft_strdup(path);
		return (1);
	}
	return (0);
}

static int	rewrite_oldpwd(t_list *environ, char *path)
{
	if (ft_strncmp(environ->content, "OLDPWD=", 7) == 0)
	{
		free(environ->content);
		environ->content = ft_strdup(path);
		return (1);
	}
	else if (ft_strncmp(environ->content, "OLDPWD", 7) == 0)
	{
		free(environ->content);
		environ->content = ft_strdup(path);
		return (1);
	}
	return (0);
}

/*
**	@brief	rewrite $OLDPWD and $PWD
**
**	@param	old		old path
**	@param	new		new path
**	@param	environ		list of environment variables
*/

void	write_oldnew_pwd(char *old, t_list *environ)
{
	char	*tmp;
	char	*tmp2;
	char	*new;
	int		flag;

	new = malloc(255);
	tmp = ft_strjoin("PWD=", getcwd(new, 255));
	tmp2 = ft_strjoin("OLDPWD=", old);
	flag = 0;
	while (environ)
	{
		flag += rewrite_pwd(environ, tmp);
		flag += rewrite_oldpwd(environ, tmp2);
		if (flag == 2)
			break ;
		environ = environ->next;
	}
	g_gl.status = 0;
	free(new);
	free(tmp);
	free(tmp2);
}

int	validate_cd(char *ptr, char *newpath)
{
	if (!ptr)
	{
		print_error("cd", NULL, strerror(12));
		free(ptr);
		g_gl.status = 12;
		return (0);
	}
	if (newpath != NULL && ft_strlen(newpath) > 255)
	{
		print_error("cd", newpath, "File name too long");
		free(ptr);
		g_gl.status = 1;
		return (0);
	}
	return (1);
}
