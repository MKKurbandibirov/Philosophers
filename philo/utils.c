/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 09:56:10 by magomed           #+#    #+#             */
/*   Updated: 2022/02/21 14:41:16 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec * 0.001));
}

time_t	delta_time(time_t time)
{
	if (time > 0)
		return (get_time() - time);
	return (0);
}

void	ft_usleep(time_t ms)
{
	time_t	time;

	time = get_time();
	usleep(ms * 920);
	while (get_time() < time + ms)
		usleep(ms * 3);
}

int	check_death(t_philo *ph, t_info *info)
{
	long long	time;

	time = delta_time(ph->last_eat);
	if (time > info->time_to_die)
	{
		print_status(ph, info, "is dead!");
		info->is_dead = 1;
		return (1);
	}
	return (0);
}
