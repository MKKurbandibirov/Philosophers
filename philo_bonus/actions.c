/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magomed <magomed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 10:05:12 by magomed           #+#    #+#             */
/*   Updated: 2022/02/12 10:43:12 by magomed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	eating(t_philo *ph, t_info *info)
{
	sem_wait(info->forks);
	if (print_status(ph, info, "has taken a fork!"))
		return (1);
	sem_wait(info->forks);
	if (print_status(ph, info, "has taken a fork!"))
		return (1);
	if (print_status(ph, info, "is eating!"))
		return (1);
	ph->last_eat = get_time();
	ph->nbr_of_ate++;
	usleep(info->time_to_eat * 1000);
	sem_post(info->forks);
	sem_post(info->forks);
	return (0);
}

int	sleeping(t_philo *ph, t_info *info)
{
	if (ph->nbr_of_ate < info->nbr_to_eat)
	{
		if (print_status(ph, info, "is sleeping!"))
			return (1);
		usleep(info->time_to_sleep * 1000);
		return (0);
	}
	return (1);
}

int	thinking(t_philo *ph, t_info *info)
{
	if (ph->nbr_of_ate < info->nbr_to_eat)
		return (print_status(ph, info, "is thinking!"));
	return (1);
}

int	print_status(t_philo *ph, t_info *info, char *status)
{
	if (info->is_dead)
	{
		sem_wait(info->write);
		printf("%-10lld %d %s\n", delta_time(info->start_time), ph->id, status);
		sem_post(info->main_lock);
		return (1);
	}
	else
	{
		sem_wait(info->write);
		printf("%-10lld %d %s\n", delta_time(info->start_time), ph->id, status);
		sem_post(info->write);
		return (0);
	}
}
