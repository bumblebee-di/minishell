/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjack <tjack@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 12:52:55 by tjack             #+#    #+#             */
/*   Updated: 2021/05/13 12:52:58 by tjack            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	create_file1(t_par *par, char **filename, int mode1, int mode2)
{
	int	fd;

	fd = open(par->filename, mode1, mode2);
	if (fd == -1)
	{
		print_error(par->filename, NULL, strerror(errno));
		g_gl.status = 1;
		par->call_prompt = 1;
	}
	else
	{
		close(fd);
		*filename = ft_strdup(par->filename);
	}
	free(par->filename);
	par->filename = NULL;
}

static void	create_file(t_par *par, int redir)
{
	if (redir == 1)
		create_file1(par, &par->ri, O_RDONLY, 0);
	else if (redir == 2)
		create_file1(par, &par->ro, O_WRONLY | O_TRUNC | O_CREAT,
			0644);
	else if (redir == 3)
		create_file1(par, &par->aro, O_WRONLY | O_APPEND | O_CREAT,
			0644);
	else
		return ;
}

static void	fill_filename(t_par *par, const char *data, int redir)
{
	size_t	size;

	size = 1;
	skip_spaces(par, data);
	while (data[par->i] && (data[par->i] != ' ' || (data[par->i] == ' '
				&& data[par->i - 1] == '\\')) && data[par->i] != '<'
		&& data[par->i] != '>' && data[par->i] != '|')
	{
		if (data[par->i] == '\\')
			par->i++;
		par->filename = (char *)realloc(par->filename, sizeof(char)
				* (size + 1));
		par->filename[size - 1] = data[par->i++];
		par->filename[size++] = '\0';
	}
	if (!par->filename)
	{
		ft_putendl_fd("binara 11: syntax error", STDERR_FILENO);
		g_gl.status = 258;
		par->call_prompt = 1;
		return ;
	}
	skip_spaces(par, data);
	create_file(par, redir);
}

void	set_redir_and_clean_prev_filename(t_par *par, int *redir, int num)
{
	if (redir != NULL && num != 0)
		*redir = num;
	if (par->ri)
	{
		free(par->ri);
		par->ri = NULL;
	}
	if (par->ro)
	{
		free(par->ro);
		par->ro = NULL;
	}
	if (par->aro)
	{
		free(par->aro);
		par->aro = NULL;
	}
}

void	parse_files(t_par *par, const char *data)
{
	int	redir;

	if (data[par->i] == '<')
		set_redir_and_clean_prev_filename(par, &redir, 1);
	else if (data[par->i] == '>')
	{
		if (data[par->i + 1] != '>')
			set_redir_and_clean_prev_filename(par, &redir, 2);
		else
		{
			set_redir_and_clean_prev_filename(par, &redir, 3);
			par->i++;
		}
	}
	else
		return ;
	par->i++;
	fill_filename(par, data, redir);
	skip_spaces(par, data);
}
