/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoat <bgoat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 15:43:28 by bgoat             #+#    #+#             */
/*   Updated: 2021/05/11 13:37:18 by bgoat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <fcntl.h>

static char	**get_path(t_list *environ)
{
	char	*ptr;
	char	**arr;

	ptr = NULL;
	arr = NULL;
	while (environ)
	{
		if (ft_strncmp("PATH=", environ->content, 5) == 0)
		{
			ptr = ft_substr(environ->content, 5, ft_strlen(environ->content));
			arr = ft_split(ptr, ':');
			free(ptr);
			return (arr);
		}
		environ = environ->next;
	}
	return (NULL);
}

static void	try_path(char **path, t_lcmd *lcmd)
{
	char	*tmp;
	int		i;
	int		fd;
	int		flag;

	i = -1;
	flag = 0;
	while (path[++i])
	{
		if (flag == 0)
		{
			tmp = path[i];
			path[i] = ft_strjoin(path[i], lcmd->arg[0]);
			free(tmp);
			fd = open(path[i], O_RDONLY);
			close (fd);
			if (fd != -1)
			{
				free(lcmd->arg[0]);
				lcmd->arg[0] = ft_strdup(path[i]);
				flag = 1;
			}
		}
		free(path[i]);
	}
}

void	get_pathname(t_lcmd *lcmd, t_list *environ)
{
	char	**path;
	char	*tmp;
	int		fd;

	fd = open(lcmd->arg[0], O_RDONLY);
	path = NULL;
	tmp = NULL;
	if (fd == -1)
	{
		tmp = lcmd->arg[0];
		lcmd->arg[0] = ft_strjoin("/", lcmd->arg[0]);
		free(tmp);
		path = get_path(environ);
		if (!path)
		{
			close(fd);
			return ;
		}
		try_path(path, lcmd);
	}
	close (fd);
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
	{
		free(arr[i]);
		i++;
	}
	if (arr)
		free(arr);
}
