/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 18:12:48 by Cutku             #+#    #+#             */
/*   Updated: 2023/06/03 23:14:45 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	printf_mutex(t_philo *philo, char *message)
{
	pthread_mutex_lock(philo->args->done);
	printf(message, (int)(time_in_ms() - philo->args->start), philo->id);
	pthread_mutex_unlock(philo->args->done);
}

pthread_mutex_t	*init_mutex(t_args *args)
{
	int				i;
	pthread_mutex_t	*forks;

	forks = my_malloc(args->garbage, args->num_philo, sizeof(pthread_mutex_t));
	i = -1;
	while (++i < args->num_philo)
		pthread_mutex_init(&forks[i], NULL);
	return (forks);
}

void	destroy_mutexes(t_philo *philo, t_args *args)
{
	int	i;

	pthread_mutex_destroy(args->last_eat);
	pthread_mutex_destroy(args->done);
	pthread_mutex_destroy(args->printf_mutex);
	i = -1;
	while (++i < args->num_philo)
		pthread_mutex_destroy(&philo->forks[i]);
}
