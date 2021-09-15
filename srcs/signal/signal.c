/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoat <bgoat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 16:49:12 by bgoat             #+#    #+#             */
/*   Updated: 2021/05/12 15:25:51 by bgoat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/signals.h"
#include "../../includes/parser.h"

static void	sigquit(int sig)
{
	int	i;

	i = 0;
	if (sig == SIGQUIT)
	{
		if (g_gl.pid)
		{
			while (g_gl.pid[i])
			{
				kill(g_gl.pid[i], SIGQUIT);
				i++;
			}
		}
	}
	return ;
}

static void	sigint(int sig)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (sig == SIGINT)
	{
		if (g_gl.pid)
		{
			while (g_gl.pid[i])
			{
				flag = 1;
				kill(g_gl.pid[i], SIGINT);
				i++;
			}
		}
		if (flag == 0)
		{
			write (1, "\n", 1);
			print_promt();
		}
		g_gl.status = 1;
	}
	return ;
}

void	signal_handler(void)
{
	if (signal(SIGQUIT, sigquit) == SIG_ERR)
		ft_putendl_fd("can't catch SIGQUIT", 1);
	if (signal(SIGINT, sigint) == SIG_ERR)
		ft_putendl_fd("can't catch SIGINT", 1);
	return ;
}
