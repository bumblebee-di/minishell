/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_executor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoat <bgoat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 15:48:46 by bgoat             #+#    #+#             */
/*   Updated: 2021/05/11 19:39:01 by bgoat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/pipe_redir.h"
#include "../../includes/termcap.h"

static void	simple_non_builtin(t_lcmd *lcmd, t_list **environ)
{
	char	**env;

	redir_handler(lcmd);
	env = create_array_from_list(*environ);
	get_pathname(lcmd, *environ);
	if (execve(lcmd->arg[0], lcmd->arg, env) == -1)
	{
		if (find_node(*environ, "PATH") != -1)
			print_error(&lcmd->arg[0][1], NULL, "command not found");
		else
			print_error(&lcmd->arg[0][1], NULL, "no such file or directory");
	}
	free_array(env);
	free(g_gl.pid);
	exit(127);
}

static void	get_simple_cmd_exit_status(int status)
{
	g_gl.status = WEXITSTATUS(status);
	g_gl.sig = WTERMSIG(status);
	if (g_gl.sig == 3)
	{
		ft_putendl_fd("Quit: 3", 1);
		g_gl.status = 128 + g_gl.sig;
	}
	else if (g_gl.sig == 2)
	{
		write(1, "\n", 1);
		g_gl.status = 128 + g_gl.sig;
	}
}

static void	simple_command(t_lcmd *lcmd, t_list **environ, t_dlist *ddl)
{
	int		status;
	int		fdout;

	fdout = fd_handler(lcmd);
	if (check_for_builtin(lcmd, environ, fdout, ddl) == 0)
	{
		if (fdout != 1)
			close(fdout);
		g_gl.pid[0] = fork();
		if (g_gl.pid[0] < 0)
			write(STDIN_FILENO, "fork error\n", 11);
		else if (g_gl.pid[0] == 0)
			simple_non_builtin(lcmd, environ);
		g_gl.pid[0] = waitpid(*g_gl.pid, &status, 0);
		if (g_gl.pid[0] < 0)
			write(STDERR_FILENO, "waitpid error\n", 14);
		get_simple_cmd_exit_status(status);
	}
	if (fdout != 1)
		close(fdout);
}

void	executor(t_lcmd *lcmd, t_list **environ, t_dlist *ddl)
{
	int		size;

	ddl->cmd_type = 0;
	size = ft_lcmdsize(lcmd);
	g_gl.pid = malloc((size) * sizeof(int));
	if (size == 1)
	{
		ddl->cmd_type = 1;
		simple_command(lcmd, environ, ddl);
	}
	else if (size != 0)
		complex_command(lcmd, environ, size, ddl);
	free(g_gl.pid);
}
