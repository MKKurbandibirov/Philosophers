/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magomed <magomed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 09:18:59 by magomed           #+#    #+#             */
/*   Updated: 2022/02/07 17:42:54 by magomed          ###   ########.fr       */
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
	long long		last_eat;
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
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				nbr_to_eat;
	int				is_dead;
	long			start_time;
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
** Time handling functions
*/
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
void	mutex_destroy(t_info *info);
void	free_info(t_info *info);
#endif