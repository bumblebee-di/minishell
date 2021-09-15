/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_redir.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoat <bgoat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 13:17:51 by bgoat             #+#    #+#             */
/*   Updated: 2021/05/04 12:49:27 by bgoat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_REDIR_H
# define PIPE_REDIR_H
# include "parser.h"

/*
**	pipe_redir.c
*/

void	pipe_handler(t_lcmd *lcmd, int **fd, int i, int n_proc);
void	redir_handler(t_lcmd *lcmd);
int		fd_handler(t_lcmd *lcmd);

/*
**	pipe_redir_utils.c
*/

void	close_all_fd_for_process(int n_proc, int **fd);
int		**create_fd_array(int n_proc);
void	free_fd_array(int **fd, int n_proc);

#endif
