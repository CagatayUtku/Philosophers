/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 03:09:45 by Cutku             #+#    #+#             */
/*   Updated: 2023/05/29 19:08:59 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <limits.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>

typedef struct s_args
{
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_eating;
	pthread_mutex_t	*printf_mutex;
	pthread_mutex_t	*last_eat;
	pthread_mutex_t	*done;
	int				start;
	pthread_t		control;

}	t_args;

typedef struct s_philo
{
	int				id;
	int				done;
	pthread_t		thread_id;
	u_int64_t		start_eat;
	u_int64_t		start_sleep;
	u_int64_t		start_think;
	t_args			*args;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	pthread_mutex_t	*forks;
	u_int64_t		last_eat;

}	t_philo;

//control.c
void			*control_philo(void *arg);
void			control_thread(t_philo *philo, t_args *args);
void			finish_process(t_philo *philo, int x);
//create_threads.c
void			create_even_philo(t_philo *philo);
void			create_odd_philo(t_philo *philo);
//libft_funcs.c
int				ft_atoi(const char *str);
int				ft_isdigit(int c);
//my_sleep.c
long int		time_in_ms(void);
void			my_sleep(t_philo *philo, int process_time);
//process.c
void			eat(t_philo *philo);
void			*philo_routine(void *arg);
//init_structs.c
void			init_args(t_args *args, char **argv);
void			init_philo(t_philo *philo, t_args *args);
//mutex.c
void			printf_mutex(t_philo *philo, char *message);
pthread_mutex_t	*init_mutex(t_args *args);

int	check_is_done(t_philo *philo);

#endif