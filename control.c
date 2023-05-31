/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 18:09:15 by Cutku             #+#    #+#             */
/*   Updated: 2023/05/29 19:08:42 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*control_philo(void *arg)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)arg;
	i = 0;
	while (1)
	{
		pthread_mutex_lock(philo->args->last_eat);
		if ((int)(time_in_ms() - philo[i].last_eat) >= philo->args->time_to_die)
		{
			pthread_mutex_unlock(philo->args->last_eat);
			finish_process(philo, i);
			break ;
		}
		pthread_mutex_unlock(philo->args->last_eat);
		++i;
		if (philo->args->num_philo == i)
			i = 0;
	}
	return (NULL);
}

void	control_thread(t_philo *philo, t_args *args)
{
	if (pthread_create(&args->control, NULL, &control_philo, philo) != 0)
		printf("Error in create thread\n");
}

void	finish_process(t_philo *philo, int x)
{
	int	i;

	pthread_mutex_lock(philo->args->done);
	i = -1;
	while (++i < philo->args->num_philo)
		philo[i].done = 1;
	printf("%d -> %d is dead.\n", (int)(time_in_ms() - philo->args->start), philo[x].id);
	pthread_mutex_unlock(philo->args->done);
}
