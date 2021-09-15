/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoat <bgoat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 20:17:17 by bgoat             #+#    #+#             */
/*   Updated: 2021/05/11 15:19:28 by bgoat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"

void	print_error(char *func, char *name, char *message)
{
	ft_putstr_fd("binara11: ", STDERR_FILENO);
	ft_putstr_fd(func, STDERR_FILENO);
	if (name)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		if (name[0] == '\0')
			ft_putstr_fd("\"\"", STDERR_FILENO);
		else
		{
			while (*name)
			{
				if (*name == '$' && *(name + 1) == '?')
				{
					ft_putnbr_fd(g_gl.status, 2);
					name++;
				}
				else
					ft_putchar_fd(*(name), 2);
				name++;
			}
		}
	}
	if (func)
		ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(message, STDERR_FILENO);
}
