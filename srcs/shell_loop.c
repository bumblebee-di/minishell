/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoat <bgoat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 15:48:37 by bgoat             #+#    #+#             */
/*   Updated: 2021/05/13 12:50:38 by bgoat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/termcap.h"
#include "../includes/signals.h"

void	print_promt(void)
{
	write(STDOUT_FILENO, "\x1B[35m", 6);
	write(STDOUT_FILENO, "binara11> ", 10);
	write(STDOUT_FILENO, "\x1B[0m", 5);
}

void	copy_env_to_environ(char **env, t_list **environ)
{
	int		i;
	char	*str;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "OLDPWD=", 7) == 0)
			ft_lstadd_back(environ, ft_lstnew(ft_substr(env[i], 0, 6)));
		else if (ft_strncmp(env[i], "SHLVL", 6) == 0 || \
			ft_strncmp(env[i], "SHLVL=", 6) == 0)
		{
			str = write_shlvl(env[i]);
			ft_lstadd_back(environ, ft_lstnew(ft_strdup(str)));
			free(str);
		}
		else
			ft_lstadd_back(environ, ft_lstnew(ft_strdup(env[i])));
		i++;
	}
}

static void	init_ddl_lcmd(t_dlist **ddl, t_lcmd **lcmd)
{
	*lcmd = NULL;
	*ddl = NULL;
	*ddl = (t_dlist *) malloc(sizeof(t_dlist));
	(*ddl)->head = NULL;
	(*ddl)->temp2 = NULL;
	(*ddl)->history = 0;
	add_back(ddl);
}

static int	disjoin_parse_execute(t_lcmd **lcmd, t_list **environ,
		t_dlist **ddl)
{
	int	i;

	if (disjoin_data(&(*ddl)->tail))
	{
		add_back(ddl);
		return (1);
	}
	if ((*ddl)->tail->data_ar)
	{
		i = 0;
		while ((*ddl)->tail->data_ar[i])
		{
			if (parser(lcmd, (*ddl)->tail->data_ar[i], *environ))
			{
				ft_lcmdclear(lcmd, (void *) free_array);
				break ;
			}
			executor(*lcmd, environ, *ddl);
			ft_lcmdclear(lcmd, (void *) free_array);
			i++;
		}
	}
	add_back(ddl);
	return (0);
}

void	shell_loop(t_list **environ)
{
	t_lcmd			*lcmd;
	t_dlist			*ddl;
	struct termios	term;
	struct termios	save;

	init_ddl_lcmd(&ddl, &lcmd);
	g_gl.status = 0;
	save_att(&save);
	signal_handler();
	while (1)
	{
		prepare_tty(&term);
		print_promt();
		read_cmd(&ddl);
		set_save(&save);
		if (check_final_backslash(&ddl))
			continue ;
		else if (ddl->tail && ddl->tail->data
			&& ddl->tail->data[ddl->tail->data_size - 2] != '\\')
		{
			if (disjoin_parse_execute(&lcmd, environ, &ddl))
				continue ;
		}
	}
}
