/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 18:12:48 by Cutku             #+#    #+#             */
/*   Updated: 2023/05/29 18:39:16 by Cutku            ###   ########.fr       */
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

	forks = malloc(sizeof(pthread_mutex_t) * args->num_philo);
	i = -1;
	while (++i < args->num_philo)
		pthread_mutex_init(&forks[i], NULL);
	return (forks);
}
