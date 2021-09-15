/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoat <bgoat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 15:48:55 by bgoat             #+#    #+#             */
/*   Updated: 2021/05/04 14:09:50 by bgoat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/termcap.h"

int	main(int argc, char **argv, char **env)
{
	t_list	*environ;

	environ = NULL;
	(void)argv;
	if (argc == 1)
	{
		tty_check();
		copy_env_to_environ(env, &environ);
		shell_loop(&environ);
	}
	else
		ft_putendl_fd("Unnecessary arguments", STDIN_FILENO);
	return (0);
}
