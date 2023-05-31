/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 18:12:11 by Cutku             #+#    #+#             */
/*   Updated: 2023/05/27 18:12:23 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_odd_philo(t_philo *philo)
{
	int	i;

	i = 1;
	while (i < philo->args->num_philo)
	{
		if (pthread_create(&philo[i].thread_id, NULL, &philo_routine, &philo[i]) != 0)
			printf("Error in create thread\n");
		i += 2;
	}
}

void	create_even_philo(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->args->num_philo)
	{
		if (pthread_create(&philo[i].thread_id, NULL, &philo_routine, &philo[i]) != 0)
			printf("Error in create thread\n");
		i += 2;
	}
}
