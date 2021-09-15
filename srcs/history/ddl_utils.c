/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ddl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjack <tjack@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 12:52:37 by tjack             #+#    #+#             */
/*   Updated: 2021/05/13 12:52:39 by tjack            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	save_and_restore_line(t_dlist **ddl, t_node **cur)
{
	if ((*cur)->data)
	{
		(*ddl)->temp2 = ft_strdup((*cur)->data);
		free((*cur)->data);
	}
	else
		(*ddl)->temp2 = NULL;
	(*cur)->data = ft_strdup((*cur)->temp);
	(*cur)->data_size = ft_strlen((*cur)->temp) + 1;
	(*cur)->init_flag = 0;
	free((*cur)->temp);
}

static void	push_new_value_to_the_end(t_dlist **ddl, t_node **cur)
{
	*cur = get_last((*ddl)->head);
	if ((*cur)->data)
		free((*cur)->data);
	if ((*ddl)->temp2)
	{
		(*cur)->data = ft_strdup((*ddl)->temp2);
		(*cur)->data_size = ft_strlen((*ddl)->temp2) + 1;
		free((*ddl)->temp2);
	}
	else
	{
		(*cur)->data = NULL;
		(*cur)->data_size = 1;
	}
}

int	append_ddl_char(t_dlist **ddl, t_node **cur, const char *buf)
{
	int	i;

	i = 0;
	while (buf[i] && buf[i] != '\n')
	{
		(*cur)->data_size++;
		(*cur)->data = (char *)realloc((*cur)->data, sizeof(char)
				* (*cur)->data_size);
		(*cur)->data[(*cur)->data_size - 2] = buf[i];
		(*cur)->data[(*cur)->data_size - 1] = '\0';
		i++;
	}
	if (buf[i] == '\n')
	{
		if ((*ddl)->history && (*cur)->temp)
		{
			save_and_restore_line(ddl, cur);
			push_new_value_to_the_end(ddl, cur);
			(*ddl)->history = 0;
		}
		return (1);
	}
	return (0);
}

t_node	*get_last(t_node *head)
{
	t_node	*temp;

	temp = head;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

void	add_back(t_dlist **ddl)
{
	t_node	*temp;

	temp = (*ddl)->head;
	(*ddl)->tail = (t_node *)malloc(sizeof(t_node));
	(*ddl)->tail->data = NULL;
	(*ddl)->tail->data_size = 1;
	(*ddl)->tail->next = NULL;
	(*ddl)->tail->temp = NULL;
	(*ddl)->tail->init_flag = 0;
	if ((*ddl)->head == NULL)
	{
		(*ddl)->tail->prev = NULL;
		(*ddl)->head = (*ddl)->tail;
		return ;
	}
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = (*ddl)->tail;
	(*ddl)->tail->prev = temp;
}
