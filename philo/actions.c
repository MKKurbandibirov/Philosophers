/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magomed <magomed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 10:05:12 by magomed           #+#    #+#             */
/*   Updated: 2022/02/07 18:29:56 by magomed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int eating(t_philo *ph, t_info *info)
{
	if (pthread_mutex_lock(&info->forks[ph->l_f]))
		return (1);
	if (print_status(ph, info, "has taken a fork!"))
		return (1);
	if (pthread_mutex_lock(&info->forks[ph->r_f]))
		return (1);
	if (print_status(ph, info, "has taken a fork!"))
		return (1);
	if (print_status(ph, info, "is eating!"))
		return (1);
	ph->last_eat = get_time();
	usleep(info->time_to_eat * 1000);
	if (pthread_mutex_unlock(&info->forks[ph->l_f]))
		return (1);
	if (pthread_mutex_unlock(&info->forks[ph->r_f]))
		return (1);
	ph->nbr_of_ate++;
	return (0);
}

int	sleeping(t_philo *ph, t_info *info)
{
	if (print_status(ph, info, "is sleeping!"))
		return (1);
	usleep(info->time_to_sleep * 1000);
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
	if (pthread_mutex_lock(&info->write))
		return (1);
	printf("%-10lld %d %s\n", delta_time(info->start_time), ph->id, status);
	if (pthread_mutex_unlock(&info->write))
		return (1);
}