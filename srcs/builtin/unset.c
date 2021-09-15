/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoat <bgoat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 12:42:16 by bgoat             #+#    #+#             */
/*   Updated: 2021/05/12 14:21:15 by bgoat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
**	@brief	checks if arguments for unset cmd are valid
**
**	@param	arg		arhument to validate
**	@return	int		1 if arg is valid, otherwise 0
*/

static int	validate_unset_arg(char *arg)
{
	int	i;

	i = 0;
	if (arg[0] == '\0')
	{
		print_error("unset", arg, "not a valid identifier");
		g_gl.status = 1;
		return (0);
	}
	while (arg[i])
	{
		if (isalpha(arg[i]) || arg[i] == '_')
			i++;
		else
		{
			print_error("unset", arg, "not a valid identifier");
			g_gl.status = 1;
			return (0);
		}
	}
	return (1);
}

/*
**	@brief	finds node that has arg as its content
**
**	@param	environ		list of environment var
**	@param	arg		line to search
**	@return	int		number of node with content if succes, -1 if failure
*/

int	find_node(t_list *environ, char *arg)
{
	char	*tmp;
	int		i;
	int		len;

	i = 0;
	tmp = ft_strjoin(arg, "=");
	len = ft_strlen(arg);
	while (environ)
	{
		if (ft_strncmp(environ->content, arg, len + 1) == 0 || \
			ft_strncmp(environ->content, tmp, len + 1) == 0)
		{
			free(tmp);
			return (i);
		}
		environ = environ->next;
		i++;
	}
	free(tmp);
	return (-1);
}

/*
**	@brief	delete head of list and ret new
**
**	@param	environ		list of environment var
**	@return	t_list**	pointer to new head of list
*/

t_list	**ft_lstdelhead(t_list **environ)
{
	t_list	*prev;

	prev = *environ;
	if (*environ != NULL)
	{
		*environ = prev->next;
		free(prev->content);
		free(prev);
	}
	return (environ);
}

/*
**	@brief	delete node in list
**
**	@param	environ		list of environment var
**	@param	n		number of node to delete
*/

void	ft_lstdelnode(t_list **environ, int n)
{
	t_list	*prev;
	t_list	*next;

	prev = *environ;
	if (*environ == NULL)
		return ;
	while (--n > 0)
		prev = prev->next;
	if (prev == NULL || prev->next == NULL)
		return ;
	next = prev->next->next;
	free(prev->next->content);
	free(prev->next);
	prev->next = next;
}

/*
**	@brief	unset function
**
**	@param	lcmd		list of struct with cmd and arg
**	@param	environ		list of environment var
*/

void	builtin_unset(t_lcmd *lcmd, t_list **environ)
{
	int	i;
	int	n;
	int	check;

	check = 0;
	i = 1;
	while (lcmd->arg[i])
	{
		check = validate_unset_arg(lcmd->arg[i]);
		if (check)
		{
			n = find_node(*environ, lcmd->arg[i]);
			if (n == 0)
				environ = ft_lstdelhead(environ);
			else if (n > 0)
				ft_lstdelnode(environ, n);
		}
		check = 0;
		i++;
	}
	g_gl.status = 0;
}
