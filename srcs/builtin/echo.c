/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoat <bgoat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 15:16:51 by bgoat             #+#    #+#             */
/*   Updated: 2021/05/11 15:31:19 by bgoat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/termcap.h"

static void	print_echo_arg(char *arg, int fd)
{
	int	j;

	j = 0;
	while (arg[j])
	{
		if (arg[j] == '$' && arg[j + 1] == '?')
		{
			ft_putnbr_fd(g_gl.status, fd);
			g_gl.status = 0;
			j++;
		}
		else
			ft_putchar_fd(arg[j], fd);
		j++;
	}
}

/*
**	@brief	realisation of echo command
**
**	@param	lcmd		list of structure with args
*/

void	builtin_echo(t_lcmd *lcmd, int fd)
{
	int		n_option;
	int		i;
	char	*str;

	i = 1;
	n_option = 1;
	while (lcmd->arg[i] && lcmd->arg[i][0] == '-')
	{
		str = ft_strtrim(&lcmd->arg[i][1], "n");
		free(str);
		if (*str != 0)
			break ;
		i++;
		n_option = 0;
	}
	while (lcmd->arg[i])
	{
		print_echo_arg(lcmd->arg[i], fd);
		if (lcmd->arg[i + 1])
			write(fd, " ", 1);
		i++;
	}
	if (n_option != 0)
		write(fd, "\n", 1);
	g_gl.status = 0;
}
