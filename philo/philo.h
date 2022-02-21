/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 09:18:59 by magomed           #+#    #+#             */
/*   Updated: 2022/02/21 15:34:06 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

/*
** Structures
*/
typedef struct s_philo
{
	int				id;
	time_t			last_eat;
	int				nbr_of_ate;
	int				l_f;
	int				r_f;
	pthread_t		thread;
	pthread_t		control;
	struct s_info	*info;
}	t_philo;

typedef struct s_info
{
	int				ph_nbr;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				nbr_to_eat;
	int				is_dead;
	time_t			start_time;
	pthread_mutex_t	write;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}	t_info;

/*
** Utils functions
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
time_t		get_time(void);
time_t		delta_time(time_t time);
void		ft_usleep(time_t ms);

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
void		mutex_destroy(t_info *info);
void		free_info(t_info *info);
#endif