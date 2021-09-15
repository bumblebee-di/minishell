/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_executor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoat <bgoat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 15:48:46 by bgoat             #+#    #+#             */
/*   Updated: 2021/05/11 19:41:27 by bgoat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/pipe_redir.h"
#include "../../includes/termcap.h"

static void	complex_non_builtin(t_lcmd *lcmd, t_list **environ, int n_proc, \
	int **fd)
{
	char	**env;

	env = create_array_from_list(*environ);
	get_pathname(lcmd, *environ);
	close_all_fd_for_process(n_proc, fd);
	g_gl.status = execve(lcmd->arg[0], lcmd->arg, env);
	if (g_gl.status < 0)
	{
		if (find_node(*environ, "PATH") != -1)
			print_error(&lcmd->arg[0][1], NULL, "command not found");
		else
			print_error(&lcmd->arg[0][1], NULL, "no such file or directory");
	}
	free_array(env);
	exit(127);
}

static void	wait_for_child_process(int n_proc)
{
	int	status;
	int	i;

	i = 0;
	while (i < n_proc)
	{
		waitpid(g_gl.pid[i], &status, 0);
		g_gl.sig = WTERMSIG(status);
		if (g_gl.sig == 2 && g_gl.status != 130)
		{
			write(1, "\n", 1);
			g_gl.status = 128 + g_gl.sig;
		}
		i++;
	}
	g_gl.status = WEXITSTATUS(status);
}

static int	create_child_process(int i)
{
	g_gl.pid[i] = fork();
	if (g_gl.pid[i] < 0)
	{
		write(STDIN_FILENO, "fork error\n", 11);
		return (0);
	}
	else if (g_gl.pid[i] == 0)
		return (1);
	return (0);
}

void	complex_command(t_lcmd *lcmd, t_list **environ, int n_proc, \
	t_dlist *ddl)
{
	t_lcmd	*head;
	int		**fd;
	int		i;

	i = 0;
	fd = create_fd_array(n_proc);
	head = lcmd;
	while (i < n_proc)
	{
		if (lcmd != head)
			g_gl.status = 0;
		if (create_child_process(i) == 1)
		{
			pipe_handler(lcmd, fd, i, n_proc);
			if (check_for_builtin(lcmd, environ, 1, ddl) == 0)
				complex_non_builtin(lcmd, environ, n_proc, fd);
			close_all_fd_for_process(n_proc, fd);
			exit (0);
		}
		lcmd = lcmd->next;
		i++;
	}
	close_all_fd_for_process(n_proc, fd);
	wait_for_child_process(n_proc);
	free_fd_array(fd, n_proc);
}
