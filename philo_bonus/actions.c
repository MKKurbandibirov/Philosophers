/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magomed <magomed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 10:05:12 by magomed           #+#    #+#             */
/*   Updated: 2022/02/09 20:35:51 by magomed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int eating(t_philo *ph, t_info *info)
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
	usleep(info->time_to_eat * 1000);
	sem_post(info->forks);
	sem_post(info->forks);
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
	sem_wait(info->write);
	printf("%-10lld %d %s\n", delta_time(info->start_time), ph->id, status);
	sem_post(info->write);
	return (0);
}