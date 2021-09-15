/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoat <bgoat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 18:26:01 by bgoat             #+#    #+#             */
/*   Updated: 2021/05/11 13:09:40 by bgoat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include <stdio.h>

static long int	atoli(char *str)
{
	int			znak;
	long int	digit;

	znak = 1;
	digit = 0;
	while (*str == ' ')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			znak = -1;
		str++;
	}
	while (*str != '\0' && ft_isdigit(*str))
	{
		digit = (digit * 10) + (*str - '0');
		if (digit > __INT_MAX__ && znak == 1)
			return ((long int)__INT_MAX__ + 1);
		else if (znak == -1 && digit > (long int)__INT_MAX__ + 1)
			return (((long int)__INT_MAX__ + 1) * znak);
		str++;
	}
	return (znak * digit);
}

static int	validate_shlvl(char *env)
{
	int	i;

	i = 0;
	while (ft_isspace(env[i]))
		i++;
	if (env[i] == '-' || env[i] == '+')
		i++;
	while (ft_isdigit(env[i]))
		i++;
	while (ft_isspace(env[i]))
		i++;
	if (env[i] == '\0')
		return (1);
	return (0);
}

static void	print_warning(int shlvl)
{
	ft_putstr_fd("binara11: warning: shell level (", 2);
	ft_putnbr_fd(shlvl, 2);
	ft_putendl_fd(") too high resetting to 1", 2);
}

static char	*get_new_shlvl_value(int shlvl)
{
	char		*str;
	char		*new_value;
	char		*nbr;

	nbr = ft_itoa(shlvl + 1);
	str = ft_strdup("SHLVL=");
	new_value = ft_strjoin(str, nbr);
	free(nbr);
	free(str);
	return (new_value);
}

char	*write_shlvl(char *env)
{
	long int	shlvl;
	char		*value;

	shlvl = 0;
	if (ft_strncmp(env, "SHLVL", 6) == 0)
		return (ft_strdup("SHLVL=0"));
	value = ft_strchr(env, '=') + 1;
	if (value == '\0' || validate_shlvl(value) == 0)
		return (ft_strdup("SHLVL=1"));
	shlvl = atoli(value);
	if (shlvl >= 1000 && shlvl < __INT_MAX__)
	{
		print_warning((int)shlvl);
		return (ft_strdup("SHLVL=1"));
	}
	else if (shlvl >= 0 && shlvl < 999)
		return (get_new_shlvl_value((int)shlvl));
	else if (shlvl == 999)
		return (ft_strdup("SHLVL="));
	return (ft_strdup("SHLVL=0"));
}
