/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 03:09:45 by Cutku             #+#    #+#             */
/*   Updated: 2023/06/06 03:46:03 by Cutku            ###   ########.fr       */
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
# include <errno.h>

typedef struct s_garbage
{
	void				*ptr;
	int					size;
	struct s_garbage	*next;

}	t_garbage;

typedef struct s_args
{
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_eating;
	int				all_ate;
	t_garbage		**garbage;
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
	int				num_eat;
	pthread_t		thread_id;
	t_args			*args;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	pthread_mutex_t	*forks;
	u_int64_t		last_eat;

}	t_philo;

//control_process.c
void			*control_philo(void *arg);
int				is_eating_done(t_philo *philo);
int				is_philo_dead(t_philo *philo, int i);
void			finish_process(t_philo *philo, int x);
//create_threads.c
void			create_even_philo(t_philo *philo);
void			create_odd_philo(t_philo *philo);
void			create_control_thread(t_philo *philo, t_args *args);
void			thread_join(t_philo *philo, t_args *args);
//libft_funcs.c
int				ft_atoi(const char *str);
int				ft_isdigit(int c);
//my_sleep.c
long int		time_in_ms(void);
void			my_sleep(t_philo *philo, int process_time);
//philo_process.c
int				check_forks(t_philo *philo);
void			eat(t_philo *philo);
void			*philo_routine(void *arg);
int				check_is_done(t_philo *philo);
//init_structs.c
void			init_args(t_args *args, char **argv, t_garbage **garbage);
void			init_philo(t_philo *philo, t_args *args);
//mutex.c
void			printf_mutex(t_philo *philo, char *message);
pthread_mutex_t	*init_mutex(t_args *args);
void			destroy_mutexes(t_philo *philo, t_args *args);
//leak_trace.c
void			*my_malloc(t_garbage **garbage, size_t count, size_t size);
void			add_garbage(t_garbage **first, void *ptr);
void			free_garbage(t_garbage **first);
int				meal(t_philo *philo);
//parse.c
int				check_args(int argc, char **argv);
int				is_all_num(char *s1);
int				is_integer(char *str);

#endif