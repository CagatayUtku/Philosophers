/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 18:09:15 by Cutku             #+#    #+#             */
/*   Updated: 2023/06/06 03:58:39 by Cutku            ###   ########.fr       */
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
		pthread_mutex_lock(philo->args->done);
		pthread_mutex_lock(philo->args->last_eat);
		if (is_philo_dead(philo, i))
			break ;
		if (is_eating_done(philo))
			break ;
		pthread_mutex_unlock(philo->args->last_eat);
		pthread_mutex_unlock(philo->args->done);
		++i;
		i = i % philo->args->num_philo;
	}
	return (NULL);
}

int	is_philo_dead(t_philo *philo, int i)
{
	if (philo->args->num_eating == 0 || \
	(philo[i].num_eat != philo->args->num_eating))
	{
		if ((int)(time_in_ms() - philo[i].last_eat) >= philo->args->time_to_die)
		{
			pthread_mutex_unlock(philo->args->last_eat);
			finish_process(philo, i);
			return (1);
		}
	}
	return (0);
}

int	is_eating_done(t_philo *philo)
{
	if (philo->args->all_ate == philo->args->num_philo)
	{
		printf("All philospher ate %d times\n", philo->args->num_eating);
		pthread_mutex_unlock(philo->args->last_eat);
		return (1);
	}
	return (0);
}

void	finish_process(t_philo *philo, int x)
{
	int	i;

	i = -1;
	while (++i < philo->args->num_philo)
		philo[i].done = 1;
	printf("%d -> %d died.\n", (int)(time_in_ms() - philo->args->start), \
	philo[x].id);
	pthread_mutex_unlock(philo->args->done);
}
