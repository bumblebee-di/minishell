/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lcmd_creator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjack <tjack@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 12:53:01 by tjack             #+#    #+#             */
/*   Updated: 2021/05/13 12:53:02 by tjack            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	filename_dup(t_lcmd **new_elem, t_par *par)
{
	if (par->ri)
	{
		(*new_elem)->ri = ft_strdup(par->ri);
		free(par->ri);
		par->ri = NULL;
	}
	if (par->ro)
	{
		(*new_elem)->ro = ft_strdup(par->ro);
		free(par->ro);
		par->ro = NULL;
	}
	if (par->aro)
	{
		(*new_elem)->aro = ft_strdup(par->aro);
		free(par->aro);
		par->aro = NULL;
	}
}

static char	**ar_dup(char **arg, size_t arg_size)
{
	size_t	m;
	char	**ar;

	if (!arg)
		return (NULL);
	m = 0;
	ar = (char **)malloc(sizeof(char *) * (arg_size + 1));
	while (m < arg_size)
	{
		ar[m] = ft_strdup(arg[m]);
		m++;
	}
	ar[arg_size] = NULL;
	return (ar);
}

static void	lcmd_init(t_lcmd **lcmd)
{
	(*lcmd)->arg = NULL;
	(*lcmd)->ri = NULL;
	(*lcmd)->ro = NULL;
	(*lcmd)->aro = NULL;
}

t_lcmd	*ft_lcmdnew(t_par *par)
{
	t_lcmd	*new_elem;

	new_elem = (t_lcmd *)malloc(sizeof(t_lcmd));
	lcmd_init(&new_elem);
	new_elem->arg = ar_dup(par->arg, par->arg_size - 1);
	filename_dup(&new_elem, par);
	new_elem->next = NULL;
	return (new_elem);
}
