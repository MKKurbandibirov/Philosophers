/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_time.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magomed <magomed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 09:56:10 by magomed           #+#    #+#             */
/*   Updated: 2022/02/12 10:40:28 by magomed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec * 0.001));
}

long long	delta_time(long long time)
{
	if (time > 0)
		return (get_time() - time);
	return (0);
}

int	check_death(t_philo *ph, t_info *info)
{
	long long	time;

	time = delta_time(ph->last_eat);
	if (time > info->time_to_die)
	{
		info->is_dead = 1;
		print_status(ph, info, "is dead!");
		return (1);
	}
	return (0);
}
