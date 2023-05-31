/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 01:16:49 by Cutku             #+#    #+#             */
/*   Updated: 2023/05/28 04:53:11 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo	*philo;
	t_args	args;
	int		i;

	if (argc > 4 && argc < 7)
	{
		philo = malloc(ft_atoi(argv[1]) * sizeof(t_philo));
		if (!philo)
			return (1);
		init_args(&args, argv);
		init_philo(philo, &args);
		create_even_philo(philo);
		usleep(500);
		create_odd_philo(philo);
		control_thread(philo, &args);
		i = -1;
		if (pthread_join(args.control, NULL) != 0)
			printf("Error in join thread\n");
		while (++i < args.num_philo)
		{
			if (pthread_join(philo[i].thread_id, NULL) != 0)
				printf("Error in join thread\n");
		}
	}
	return (0);
}