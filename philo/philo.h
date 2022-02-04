/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 17:03:32 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/02/03 14:00:22 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	long			last_eat;
	long			limit_of_life;
	int				stop;
	long			start_time;
	int				nbr_of_eat;
	// pthread_mutex_t	*l_f;
	// pthread_mutex_t	*r_f;
	int	l_f;
	int	r_f;
	struct s_info	*info;
}	t_philo;

typedef struct s_info
{
	int				ph_nbr;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				nbr_to_eat;
	int				dead;
	long			start_time;
	pthread_mutex_t	display;
	pthread_t		*death_control;
	pthread_t		*threads;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}	t_info;


int		ft_atoi(const char *str);
long	get_time(void);
void	smart_sleep(long time);
int 	validation(int ac, char **av);

void	init_info(int ac, char **av, t_info *info);
int		init_philo(t_info *info);
int		init_mutexes(t_info *info);
int		init_threads(t_info *info);

void	*ph_process(void *param);
void	*ph_death_controller(void *param);

int		join_threads(t_info *info);
void	free_all(t_info *info);
void	mutexes_destroy(t_info *info);

void    taking_forks(t_philo *philo);
int		eating(t_philo *philo);
void    sleeping(t_philo *philo);
void    thinking(t_philo *philo);
#endif