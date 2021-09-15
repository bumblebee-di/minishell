/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoat <bgoat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 15:58:26 by bgoat             #+#    #+#             */
/*   Updated: 2021/05/12 15:17:07 by bgoat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMCAP_H
# define TERMCAP_H
# include "parser.h"
# include <curses.h>
# include <term.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

/*
**	tty.c
*/

void	tty_check(void);
void	save_att(struct termios *save);
void	prepare_tty(struct termios *term);
void	set_save(struct termios *save);
void	builtin_exit(t_lcmd *lcmd, int fd, t_dlist *ddl);

#endif
