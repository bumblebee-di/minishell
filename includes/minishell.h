/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoat <bgoat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2021/05/12 16:56:41 by bgoat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/wait.h>
# include <ctype.h>
# include "parser.h"

typedef struct s_export
{
	int		eq;
	int		plus;
	char	*var;
	char	*value;
}	t_export;

void	shell_loop(t_list **environ);
void	copy_env_to_environ(char **env, t_list **environ);
void	executor(t_lcmd *lcmd, t_list **environ, t_dlist *ddl);
void	get_pathname(t_lcmd *lcmd, t_list *environ);
void	free_array(char **arr);
int		check_for_builtin(t_lcmd *lcmd, t_list **environ, int fd, t_dlist *ddl);

void	builtin_export(t_lcmd *lcmd, t_list **environ, int fd);
void	sort_print_env(t_list *environ, int fd);
char	**create_array_from_list(t_list *environ);
void	builtin_unset(t_lcmd *lcmd, t_list **environ);
void	builtin_cd(char *newpath, t_list *environ);
void	builtin_echo(t_lcmd *lcmd, int fd);
void	builtin_exit(t_lcmd *lcmd, int fd, t_dlist *ddl);
void	redir_handler(t_lcmd *lcmd);

void	write_oldnew_pwd(char *old, t_list *environ);
int		validate_cd(char *ptr, char *newpath);

void	print_error(char *func, char *name, char *message);
char	*write_shlvl(char *env);

int		find_node(t_list *environ, char *arg);

void	complex_command(t_lcmd *lcmd, t_list **environ, int n_proc, \
	t_dlist *ddl);

void	append_env(t_list *environ, t_export *export, char *arg);
void	overwrite_env(t_list *environ, t_export *export, char *arg);

#endif
