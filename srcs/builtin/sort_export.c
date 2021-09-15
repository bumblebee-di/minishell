/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoat <bgoat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 18:12:27 by bgoat             #+#    #+#             */
/*   Updated: 2021/05/05 15:53:34 by bgoat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
**	@brief	swap array's cells
**
**	@param	var		struct
**	@param	i		index of "left" cell to swap
**	@param	j		index of "right" cell to swap
*/

static void	swap_array(char **arr, int i, int j)
{
	char	*temp;

	temp = arr[j];
	arr[j] = arr[i];
	arr[i] = temp;
}

/*
**	@brief	sort array in alphabetical order
**
**	@param	var		struct
**	@param	left		index of current first
**	@param	right		index of current last
*/

static void	sort_array(char **arr, int left, int right)
{
	char	*pivot;
	int		i;
	int		j;

	i = left;
	j = right;
	pivot = arr[i + (j - i) / 2];
	while (i <= j)
	{
		while (ft_strncmp(arr[i], pivot, ft_strlen(arr[i])) < 0)
			i++;
		while (ft_strncmp(arr[j], pivot, ft_strlen(arr[j])) > 0)
			j--;
		if (i <= j)
		{
			if (ft_strncmp(arr[i], arr[j], ft_strlen(arr[j])) > 0)
				swap_array(arr, i, j);
			i++;
			j--;
		}
	}
	if (i < right)
		sort_array(arr, i, right);
	if (j > left)
		sort_array(arr, left, j);
}

/*
**	@brief	Create an array from list of environment variables
**
**	@param	arr		array itself
**	@param	environ		list
*/

char	**create_array_from_list(t_list *environ)
{
	int		i;
	char	**arr;
	int		size;

	i = 0;
	size = ft_lstsize(environ);
	arr = NULL;
	arr = (char **)malloc(sizeof(char *) * (size + 1));
	if (!arr)
		print_error("export", NULL, strerror(errno));
	while (environ != NULL)
	{
		arr[i] = ft_strdup(environ->content);
		i++;
		environ = environ->next;
	}
	arr[i] = NULL;
	return (&arr[0]);
}

/*
**	@brief	print and free array line by line
**
**	@param	arr		array
*/

static void	print_n_free_array(char **arr, int fd)
{
	int		i;
	int		k;
	char	*ptr;

	i = 0;
	while (arr[i])
	{
		ft_putstr_fd("declare -x ", fd);
		ptr = ft_strchr(arr[i], '=');
		if (ptr == NULL)
			ft_putendl_fd(arr[i], fd);
		else
		{
			k = (int)(ptr - arr[i]);
			write(fd, arr[i], k + 1);
			write(fd, "\"", 1);
			ft_putstr_fd(&arr[i][k + 1], fd);
			write(fd, "\"\n", 2);
		}
		free(arr[i]);
		i++;
	}
	free(arr);
}

/*
**	@brief	create array from list, sorts it (using quicksort), \
** prints and free array 
**	for "export" case
**
**	@param	environ		list of environment variables
*/

void	sort_print_env(t_list *environ, int fd)
{
	char	**arr;

	arr = create_array_from_list(environ);
	sort_array(arr, 0, ft_lstsize(environ) - 1);
	print_n_free_array(arr, fd);
}
