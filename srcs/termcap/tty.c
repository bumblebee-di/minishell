/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoat <bgoat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 14:50:34 by bgoat             #+#    #+#             */
/*   Updated: 2021/05/12 18:04:55 by bgoat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../includes/minishell.h"
#include "../../includes/termcap.h"

void	save_att(struct termios *save)
{
	if (tcgetattr(0, save) == -1)
	{
		ft_putstr_fd("tcgetattr error", 0);
		exit (1);
	}
}

void	tty_check(void)
{
	char	*termtype;

	if (!isatty(0))
		exit (1);
	termtype = getenv("TERM");
	if (termtype == NULL || tgetent(0, termtype) != 1)
	{
		ft_putendl_fd("Can not find terminal or termcap base.", STDERR_FILENO);
		exit (1);
	}
}

void	prepare_tty(struct termios *term)
{
	char	*termtype;

	if (tcgetattr(0, term) == -1)
	{
		ft_putstr_fd("tcgetattr error", STDERR_FILENO);
		exit (1);
	}
	term->c_lflag &= ~(ICANON | ECHO);
	if (tcsetattr(0, TCSANOW, term) == -1)
	{
		ft_putstr_fd("tcgetattr error", STDERR_FILENO);
		exit (1);
	}
	termtype = getenv("TERM");
	tgetent(0, termtype);
}

void	set_save(struct termios *save)
{
	char	*termtype;

	if (tcsetattr(0, TCSANOW, save) == -1)
	{
		ft_putstr_fd("tcgetattr error", STDERR_FILENO);
		exit (1);
	}
	termtype = getenv("TERM");
	tgetent(0, termtype);
}
