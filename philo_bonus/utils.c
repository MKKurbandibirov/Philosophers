/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 09:56:10 by magomed           #+#    #+#             */
/*   Updated: 2022/02/23 10:15:42 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

void	ft_usleep(int ms)
{
	long	time;

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
		info->is_dead = 1;
		print_status(ph, info, "is dead!");
		return (1);
	}
	return (0);
}
