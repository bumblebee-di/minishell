/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoat <bgoat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 13:13:52 by bgoat             #+#    #+#             */
/*   Updated: 2021/05/11 16:42:05 by bgoat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/pipe_redir.h"
#include "fcntl.h"

void	pipe_handler(t_lcmd *lcmd, int **fd, int i, int n_proc)
{
	if (i != 0 && !lcmd->ri)
		dup2(fd[i - 1][0], STDIN_FILENO);
	if (i != n_proc - 1 && !lcmd->ro && !lcmd->aro)
		dup2(fd[i][1], STDOUT_FILENO);
	close_all_fd_for_process(n_proc, fd);
	redir_handler(lcmd);
}

void	redir_handler(t_lcmd *lcmd)
{
	int	fdin;
	int	fdout;
	int	flags;

	flags = S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR;
	if (lcmd->ri)
	{
		fdin = open(lcmd->ri, O_RDONLY);
		dup2(fdin, 0);
		close(fdin);
	}
	if (lcmd->ro)
	{
		fdout = open(lcmd->ro, O_WRONLY | O_TRUNC | O_CREAT, flags);
		dup2(fdout, 1);
		close(fdout);
	}
	else if (lcmd->aro)
	{
		fdout = open(lcmd->aro, O_CREAT | O_WRONLY | O_APPEND, flags);
		dup2(fdout, 1);
		close(fdout);
	}
}

int	fd_handler(t_lcmd *lcmd)
{
	int	fdout;
	int	flags;

	fdout = 1;
	flags = S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR;
	if (lcmd->ro)
		fdout = open(lcmd->ro, O_WRONLY | O_TRUNC | O_CREAT, flags);
	else if (lcmd->aro)
		fdout = open(lcmd->aro, O_CREAT | O_WRONLY | O_APPEND, flags);
	return (fdout);
}
