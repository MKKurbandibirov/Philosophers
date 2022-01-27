/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 17:03:32 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/01/27 15:43:02 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <string.h>

typedef struct s_philos
{
	int				ph_nmb;
	int				cur;
	int				*is_eat;
	int				*is_sleep;
	int				*forks;
	size_t			*time;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	pthread_mutex_t	*mutex;
}	t_philos;

int	ft_atoi(const char *str);

#endif