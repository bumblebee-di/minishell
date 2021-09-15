/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lcmd_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjack <tjack@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 12:53:13 by tjack             #+#    #+#             */
/*   Updated: 2021/05/13 12:53:15 by tjack            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_lcmd	*ft_lcmdlast(t_lcmd *lst)
{
	t_lcmd	*tmp;

	tmp = lst;
	if (tmp == NULL)
		return (NULL);
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	ft_lcmdadd_back(t_lcmd **lst, t_lcmd *new)
{
	if (*lst == NULL)
		*lst = new;
	else
		ft_lcmdlast(*lst)->next = new;
}

int	ft_lcmdsize(t_lcmd *lcmd)
{
	int		i;
	t_lcmd	*tmp;

	tmp = lcmd;
	i = 0;
	while (tmp != NULL)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void	ft_lcmddelone(t_lcmd *lst, void (*del)(void *))
{
	if (lst == NULL || (*del) == NULL)
		return ;
	if (lst->arg)
		(*del)(lst->arg);
	if (lst->ri)
	{
		free(lst->ri);
		lst->ri = NULL;
	}
	if (lst->ro)
	{
		free(lst->ro);
		lst->ro = NULL;
	}
	if (lst->aro)
	{
		free(lst->aro);
		lst->aro = NULL;
	}
	free(lst);
}

void	ft_lcmdclear(t_lcmd **lst, void (*del)(void*))
{
	t_lcmd	*tmp;

	tmp = (*lst);
	if (lst == NULL || (*del) == NULL)
		return ;
	while ((*lst) != NULL)
	{
		tmp = (*lst)->next;
		ft_lcmddelone((*lst), (*del));
		(*lst) = tmp;
	}
}
