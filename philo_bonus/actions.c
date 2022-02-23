/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 10:05:12 by magomed           #+#    #+#             */
/*   Updated: 2022/02/23 10:57:27 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	eating(t_philo *ph, t_info *info)
{
	if (ph->nbr_of_ate == info->nbr_to_eat)
		return (1);
	sem_wait(info->forks);
	sem_wait(info->forks);
	if (print_status(ph, info, "has taken a fork!"))
		return (1);
	if (print_status(ph, info, "has taken a fork!"))
		return (1);
	if (print_status(ph, info, "is eating!"))
		return (1);
	ph->last_eat = get_time();
	ph->nbr_of_ate++;
	if (ph->nbr_of_ate == info->nbr_to_eat)
		sem_post(info->eat_enough);
	ft_usleep(info->time_to_eat);
	sem_post(info->forks);
	sem_post(info->forks);
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
	sem_wait(info->write);
	printf("%-10ld %d %s\n", delta_time(info->start_time), ph->id, status);
	sem_post(info->write);
	return (0);
}
