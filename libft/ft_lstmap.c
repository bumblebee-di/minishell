/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoat <bgoat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 12:56:13 by bgoat             #+#    #+#             */
/*   Updated: 2021/04/11 19:22:32 by bgoat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_el;
	t_list	*header;

	if (!lst || (*f) == NULL)
		return (NULL);
	header = ft_lstnew((*f)(lst->content));
	if (!(header))
		return (NULL);
	new_el = header;
	lst = lst->next;
	while (lst)
	{
		new_el->next = ft_lstnew((*f)(lst->content));
		if (!(new_el))
		{
			ft_lstclear(&header, (*del));
			return (NULL);
		}
		new_el = new_el->next;
		lst = lst->next;
	}
	new_el->next = NULL;
	return (header);
}
