/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoat <bgoat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 15:09:45 by bgoat             #+#    #+#             */
/*   Updated: 2021/05/12 15:14:47 by bgoat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/termcap.h"

static int	validate_exit_arg(t_lcmd *lcmd)
{
	int	ret_value;
	int	i;

	i = 0;
	ret_value = 0;
	if (lcmd->arg[1])
	{
		while (lcmd->arg[1][i])
		{
			if (!ft_isdigit(lcmd->arg[1][i]))
			{
				ret_value = 1;
				g_gl.status = 255;
			}
			i++;
		}
		if (ret_value == 0 && lcmd->arg[2])
		{
			ret_value = 2;
			g_gl.status = 1;
		}
		else if (ret_value == 0)
			g_gl.status = ft_atoi(lcmd->arg[1]);
	}
	return (ret_value);
}

/*
**	@brief	implementation of exit command
*/

void	builtin_exit(t_lcmd *lcmd, int fd, t_dlist *ddl)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	if (lcmd != NULL)
		flag = validate_exit_arg(lcmd);
	if (ddl->cmd_type == 1)
	{
		ft_putendl_fd("exit", fd);
		if (ddl->bytes_read > 1)
			free(g_gl.pid);
	}
	if (flag == 1)
		print_error("exit", lcmd->arg[1], "numeric argument required");
	else if (flag == 2)
	{
		print_error("exit", NULL, "too many arguments");
		return ;
	}
	exit (g_gl.status);
}
