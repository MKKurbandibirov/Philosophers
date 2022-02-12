/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magomed <magomed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 09:47:07 by magomed           #+#    #+#             */
/*   Updated: 2022/02/12 09:57:09 by magomed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	routine_exe(t_philo *ph, t_info *info)
{
	if (eating(ph, info))
		return (1);
	if (ph->nbr_of_ate != info->nbr_to_eat)
	{
		if (sleeping(ph, info))
			return (1);
		if (thinking(ph, info))
			return (1);
	}
	return (0);
}

static void	*control(void *param)
{
	t_philo		*ph;
	t_info		*info;

	ph = (t_philo *)param;
	info = ph->info;
	if (info->nbr_to_eat > 0)
	{
		while (info->nbr_to_eat > ph->nbr_of_ate && !info->is_dead)
			if (check_death(ph, info))
				return (NULL);
	}
	else
	{
		while (!info->is_dead)
			if (check_death(ph, info))
				return (NULL);
	}
	return (NULL);
}

static void	*routine(void *param)
{
	t_philo	*ph;
	t_info	*info;

	ph = (t_philo *)param;
	info = ph->info;
	if (pthread_create(&ph->control, NULL, control, (void *)ph))
		return (NULL);
	pthread_detach(ph->control);
	if (info->nbr_to_eat > 0)
	{
		while (info->nbr_to_eat > ph->nbr_of_ate && !info->is_dead)
			if (routine_exe(ph, info))
				break ;
	}
	else
	{
		while (!info->is_dead)
			if (routine_exe(ph, info))
				break ;
	}
	return (NULL);
}

int	create_threads(t_info *info)
{
	int	i;

	i = -1;
	info->start_time = get_time();
	while (++i < info->ph_nbr)
	{
		if (pthread_create(&info->philos[i].thread, NULL,
				routine, (void *)&info->philos[i]))
		{
			printf("Couldn't create thread!\n");
			return (1);
		}
		usleep(1000);
	}
	i = -1;
	while (++i < info->ph_nbr)
	{
		if (pthread_join(info->philos[i].thread, NULL))
		{
			printf("Couldn't join thread!\n");
			return (1);
		}
	}
	return (0);
}
