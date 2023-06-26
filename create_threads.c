/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 18:12:11 by Cutku             #+#    #+#             */
/*   Updated: 2023/06/03 23:41:47 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_odd_philo(t_philo *philo)
{
	int	i;

	i = 1;
	while (i < philo->args->num_philo)
	{
		if (pthread_create(&philo[i].thread_id, NULL, \
		&philo_routine, &philo[i]) != 0)
		{
			printf("Error in create thread\n");
			free_garbage(philo->args->garbage);
			return ;
		}
		i += 2;
	}
}

void	create_even_philo(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->args->num_philo)
	{
		if (pthread_create(&philo[i].thread_id, NULL, \
		&philo_routine, &philo[i]) != 0)
		{
			printf("Error in create thread\n");
			return ;
		}
		i += 2;
	}
	usleep(500);
}

void	create_control_thread(t_philo *philo, t_args *args)
{
	if (pthread_create(&args->control, NULL, &control_philo, philo) != 0)
	{
		printf("Error in create thread\n");
		return ;
	}
}

void	thread_join(t_philo *philo, t_args *args)
{
	int	i;

	i = -1;
	if (pthread_join(args->control, NULL) != 0)
	{
		printf("Error in join thread\n");
		return ;
	}
	while (++i < args->num_philo)
	{
		if (pthread_join(philo[i].thread_id, NULL) != 0)
		{
			printf("Error in join thread\n");
			return ;
		}
	}
}
