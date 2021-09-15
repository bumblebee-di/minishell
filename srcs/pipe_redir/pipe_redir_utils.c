/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_redir_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoat <bgoat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 13:13:50 by bgoat             #+#    #+#             */
/*   Updated: 2021/05/03 15:41:00 by bgoat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_all_fd_for_process(int n_proc, int **fd)
{
	int	j;
	int	n_pipes;

	j = 0;
	n_pipes = n_proc - 1;
	while (j < n_pipes)
	{
		close(fd[j][0]);
		close(fd[j][1]);
		j++;
	}
}

int	**create_fd_array(int n_proc)
{
	int	i;
	int	**fd;

	i = 0;
	fd = (int **)malloc(n_proc * sizeof(int *));
	if (!fd)
		return (NULL);
	while (i < n_proc - 1)
	{
		fd[i] = (int *)malloc(2 * sizeof(int));
		if (pipe(fd[i]) < 0)
		{
			ft_putendl_fd("ERROR creating pipe", 2);
			exit (-1);
		}
		i++;
	}
	return (fd);
}

void	free_fd_array(int **fd, int n_proc)
{
	int	i;

	i = 0;
	while (i < n_proc - 1)
	{
		free(fd[i]);
		i++;
	}
	free(fd);
}
