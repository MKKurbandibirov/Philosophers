/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magomed <magomed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 09:18:59 by magomed           #+#    #+#             */
/*   Updated: 2022/02/12 10:41:29 by magomed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <unistd.h>
# include <signal.h>
# include <sys/time.h>
# include <sys/wait.h>

/*
** Structures
*/
typedef struct s_philo
{
	int				id;
	long long		last_eat;
	int				nbr_of_ate;
	pid_t			pid;
	pthread_t		control;
	struct s_info	*info;
}	t_philo;

typedef struct s_info
{
	int				ph_nbr;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				nbr_to_eat;
	int				is_dead;
	long			start_time;
	sem_t			*main_lock;
	sem_t			*write;
	sem_t			*forks;
	t_philo			*philos;
}	t_info;

/*
** Validation functions
*/
int			ft_atoi(const char *str);
int			validation(int ac, char **av);

/*
** Init and create functions
*/
int			create_info(int ac, char **av, t_info *info);
int			create_threads(t_info *info);

/*
** Utils functions
*/
int			check_death(t_philo *ph, t_info *info);
long long	get_time(void);
long long	delta_time(long long time);

/*
** Action functions
*/
int			eating(t_philo *ph, t_info *info);
int			sleeping(t_philo *ph, t_info *info);
int			thinking(t_philo *ph, t_info *info);
int			print_status(t_philo *ph, t_info *info, char *status);

/*
** Free and Destry functions
*/
void		close_destroy(t_info *info);
void		free_info(t_info *info);
#endif