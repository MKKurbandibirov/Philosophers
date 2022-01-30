/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 17:03:32 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/01/30 17:06:21 by nfarfetc         ###   ########.fr       */
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
	size_t			last_eat;
	pthread_t		thread;
	pthread_mutex_t	fork;
	struct s_info	*info;
}	t_philo;

typedef struct s_info
{
	int				ph_nmb;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				nmb_to_eat;
	int				count_of_eat;
	size_t			start_time;
	t_philo			*philos;
	pthread_mutex_t	display;
	pthread_t		death_control;
}	t_info;


int	ft_atoi(const char *str);

#endif