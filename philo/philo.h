/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magomed <magomed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 17:03:32 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/02/02 11:49:05 by magomed          ###   ########.fr       */
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
	pthread_mutex_t	*l_f;
	pthread_mutex_t	*r_f;
	struct s_info	*info;
}	t_philo;

typedef struct s_info
{
	int				ph_nmb;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				nmb_to_eat;
	int				dead;
	long			start_time;
	pthread_mutex_t	display;
	pthread_t		death_control;
	pthread_t		*threads;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}	t_info;


int		ft_atoi(const char *str);
long	get_time(void);
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
#endif