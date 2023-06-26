/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 03:40:32 by Cutku             #+#    #+#             */
/*   Updated: 2023/06/06 03:41:14 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	check_args(int argc, char **argv)
{
	int	i;

	i = 0;
	while (++i < argc)
	{
		if (!is_all_num(argv[i]) || !is_integer(argv[i]))
		{
			printf("Wrong Input.\n");
			return (1);
		}
		if (ft_atoi(argv[i]) <= 0)
		{
			printf("Input has to be bigger than 0.\n");
			return (1);
		}
	}
	return (0);
}
