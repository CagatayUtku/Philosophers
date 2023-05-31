/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 18:10:38 by Cutku             #+#    #+#             */
/*   Updated: 2023/05/29 18:24:12 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!check_is_done(philo))
	{
		printf_mutex(philo, "%d -> %d is thinking.\n");
		eat(philo);
		my_sleep(philo, philo->args->time_to_sleep);
	}
	return (NULL);
}

int	check_is_done(t_philo *philo)
{
	pthread_mutex_lock(philo->args->done);
	if (philo->done)
		return (pthread_mutex_unlock(philo->args->done), 1);
	return (pthread_mutex_unlock(philo->args->done), 0);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left);
	if (check_is_done(philo))
	{
		pthread_mutex_unlock(philo->left);
		return ;
	}
	printf_mutex(philo, "%d -> %d has taken left fork.\n");
	if (philo->right == NULL)
	{
		pthread_mutex_unlock(philo->left);
		my_sleep(philo, philo->args->time_to_die + 1000);
		return ;
	}
	pthread_mutex_lock(philo->right);
	if (check_is_done(philo))
	{
		pthread_mutex_unlock(philo->right);
		return ;
	}
	printf_mutex(philo, "%d -> %d has taken right fork.\n");
	printf_mutex(philo, "%d -> %d is eating.\n");
	pthread_mutex_lock(philo->args->last_eat);
	philo->last_eat = time_in_ms();
	pthread_mutex_unlock(philo->args->last_eat);
	my_sleep(philo, philo->args->time_to_eat);
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
	if (!check_is_done(philo))
		printf_mutex(philo, "%d -> %d is sleeping.\n");
}
