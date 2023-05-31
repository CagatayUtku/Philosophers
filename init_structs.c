/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 18:13:50 by Cutku             #+#    #+#             */
/*   Updated: 2023/05/28 04:55:55 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_args(t_args *args, char **argv)
{
	args->num_philo = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	args->num_eating = ft_atoi(argv[5]);
	args->printf_mutex = malloc(sizeof(pthread_mutex_t));
	args->last_eat = malloc(sizeof(pthread_mutex_t));
	args->done = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(args->printf_mutex, NULL);
	pthread_mutex_init(args->last_eat, NULL);
	pthread_mutex_init(args->done, NULL);
	args->start = time_in_ms();
}

void	init_philo(t_philo *philo, t_args *args)
{
	int	i;

	i = -1;
	philo->forks = init_mutex(args);
	while (++i < args->num_philo)
	{
		philo[i].id = i;
		philo[i].start_eat = 0;
		philo[i].start_sleep = 0;
		philo[i].start_think = 0;
		philo[i].args = args;
		philo[i].done = 0;
		philo[i].last_eat = time_in_ms();
		philo[i].left = &philo->forks[i];
		if (args->num_philo == 1)
			philo[i].right = NULL;
		else
			philo[i].right = &philo->forks[(i + 1) % philo->args->num_philo];
	}
}
