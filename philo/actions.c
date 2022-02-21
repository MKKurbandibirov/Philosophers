/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 10:05:12 by magomed           #+#    #+#             */
/*   Updated: 2022/02/21 15:19:46 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eating(t_philo *ph, t_info *info)
{
	pthread_mutex_lock(&info->forks[ph->l_f]);
	if (print_status(ph, info, "has taken a fork!"))
		return (1);
	pthread_mutex_lock(&info->forks[ph->r_f]);
	if (print_status(ph, info, "has taken a fork!"))
		return (1);
	if (print_status(ph, info, "is eating!"))
		return (1);
	ph->last_eat = get_time();
	ft_usleep(info->time_to_eat);
	ph->nbr_of_ate++;
	pthread_mutex_unlock(&info->forks[ph->l_f]);
	pthread_mutex_unlock(&info->forks[ph->r_f]);
	return (0);
}

int	sleeping(t_philo *ph, t_info *info)
{
	if (print_status(ph, info, "is sleeping!"))
		return (1);
	ft_usleep(info->time_to_sleep);
	return (0);
}

int	thinking(t_philo *ph, t_info *info)
{
	return (print_status(ph, info, "is thinking!"));
}

int	print_status(t_philo *ph, t_info *info, char *status)
{
	if (info->is_dead)
		return (1);
	pthread_mutex_lock(&info->write);
	if (info->is_dead)
	{
		pthread_mutex_unlock(&info->write);	
		return (1);
	}
	printf("%-10ld %d %s\n", delta_time(info->start_time), ph->id, status);
	pthread_mutex_unlock(&info->write);
	return (0);
}
