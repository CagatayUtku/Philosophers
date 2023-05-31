/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 03:13:29 by Cutku             #+#    #+#             */
/*   Updated: 2023/05/16 04:58:34 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_all_num(char *s1)
{
	int	i;

	i = 0;
	if (s1[0] == '-' || s1[0] == '+')
		i++;
	while (s1[i] != '\0')
	{
		if (!(s1[i] >= '0' && s1[i] <= '9'))
			return (0);
		i++;
	}
	if (i == 1 && (s1[0] == '-' || s1[0] == '+'))
		return (0);
	return (1);
}

int	is_integer(char *str)
{
	int			i;
	int			sign;
	long int	result;

	i = 0;
	sign = 1;
	result = 0;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] <= '9' && str[i] >= '0')
	{
		result *= 10;
		result += str[i] - 48;
		i++;
		if (result > INT_MAX && sign == 1)
			return (0);
		if (result > ((long)INT_MAX + 1) && sign == -1)
			return (0);
	}
	return (1);
}

int	error_control(char **argv)
{
	int	i;
	int	j;

	j = 0;
	while (argv[j] != NULL)
		j++;
	i = 0;
	while (i < j)
	{
		if (!is_all_num(argv[i]))
			return (0);
		if (!is_integer(argv[i]))
			return (0);
		i++;
	}
	return (i);
}

int	parse_arguments(int argc, char **argv)
{
	int		i;
	char	**ptr;

	i = 0;
	while (++i < argc)
	{
		ptr = ft_split(argv[i], ' ');
		if (error_control(ptr))
		else
		{
			free_dubleptr(ptr);
			write(2, "Wrong Input\n", 13);
			return (0);
		}
		free_dubleptr(ptr);
	}
	return (1);
}