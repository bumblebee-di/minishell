/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjack <tjack@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 12:52:10 by tjack             #+#    #+#             */
/*   Updated: 2021/05/13 12:52:32 by tjack            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/termcap.h"
#include "../../includes/minishell.h"
#include "../../includes/signals.h"

static int	ft_putint(int c)
{
	return (write(STDOUT_FILENO, &c, 1));
}

static void	handle_arrow_up(t_dlist **ddl, t_node **cur)
{
	(*ddl)->history = 1;
	tputs(restore_cursor, 1, ft_putint);
	tputs(tgetstr("cd", 0), 1, ft_putint);
	(*cur) = (*cur)->prev;
	if (!(*cur)->init_flag && (*cur)->data)
	{
		(*cur)->temp = ft_strdup((*cur)->data);
		(*cur)->init_flag = 1;
	}
	ft_putstr_fd((char *)(*cur)->data, 1);
}

static void	handle_arrow_down(t_dlist **ddl, t_node **cur)
{
	(*ddl)->history = 1;
	tputs(restore_cursor, 1, ft_putint);
	tputs(tgetstr("cd", 0), 1, ft_putint);
	(*cur) = (*cur)->next;
	if ((*cur)->data && !(*cur)->init_flag)
	{
		(*cur)->temp = ft_strdup((*cur)->data);
		(*cur)->init_flag = 1;
	}
	ft_putstr_fd((char *)(*cur)->data, 1);
}

static void	handle_backspace(t_node **cur)
{
	if ((*cur)->data_size > 1)
	{
		tputs(cursor_left, 1, ft_putint);
		tputs(tgetstr("dc", 0), 1, ft_putint);
		(*cur)->data[(*cur)->data_size - 2] = '\0';
		(*cur)->data_size--;
		(*cur)->data = (char *)realloc((*cur)->data,
				sizeof(char) * ((*cur)->data_size));
		if ((*cur)->data[0] == '\0')
		{
			free((*cur)->data);
			(*cur)->data = NULL;
		}
	}
}

void	read_cmd(t_dlist **ddl)
{
	tputs(save_cursor, 1, ft_putint);
	(*ddl)->bytes_read = 1;
	(*ddl)->cur = (*ddl)->tail;
	while ((*ddl)->bytes_read)
	{
		(*ddl)->bytes_read = read(0, (*ddl)->buf, 9);
		(*ddl)->buf[(*ddl)->bytes_read] = '\0';
		if (!ft_strncmp((*ddl)->buf, "\e[A", 4) && (*ddl)->cur->prev)
			handle_arrow_up(ddl, &(*ddl)->cur);
		else if (!ft_strncmp((*ddl)->buf, "\e[B", 4) && (*ddl)->cur->next)
			handle_arrow_down(ddl, &(*ddl)->cur);
		else if (!ft_strncmp((*ddl)->buf, "\177", 2))
			handle_backspace(&(*ddl)->cur);
		if (*(*ddl)->buf == '\4' && !((*ddl)->cur->data))
		{
			(*ddl)->cmd_type = 1;
			builtin_exit(NULL, 1, *ddl);
		}
		if (*(*ddl)->buf == 10 || (*(*ddl)->buf > 31 && *(*ddl)->buf != 127))
		{
			write(1, (*ddl)->buf, (*ddl)->bytes_read);
			if (append_ddl_char(ddl, &(*ddl)->cur, (*ddl)->buf))
				break ;
		}
	}
}
