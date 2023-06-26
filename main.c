/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 01:16:49 by Cutku             #+#    #+#             */
/*   Updated: 2023/06/06 03:42:19 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	leaks(void)
{
	system("leaks philo");
}

int	main(int argc, char **argv)
{
	t_philo		*philo;
	t_garbage	*garbage;
	t_args		args;

	if (argc > 4 && argc < 7)
	{
		garbage = NULL;
		if (check_args(argc, argv))
			return (1);
		philo = my_malloc(&garbage, ft_atoi(argv[1]), sizeof(t_philo));
		init_args(&args, argv, &garbage);
		init_philo(philo, &args);
		create_even_philo(philo);
		create_odd_philo(philo);
		create_control_thread(philo, &args);
		thread_join(philo, &args);
		destroy_mutexes(philo, &args);
		free_garbage(&garbage);
	}
	else
	{
		write(2, "Wrong number of arguments!\n", 27);
		return (EINVAL);
	}
	return (0);
}
