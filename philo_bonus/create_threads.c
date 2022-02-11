/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magomed <magomed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 09:47:07 by magomed           #+#    #+#             */
/*   Updated: 2022/02/11 09:16:37 by magomed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	routine_exe(t_philo *ph,  t_info *info)
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
	t_philo 	*ph;
	t_info		*info;
	long long	time;

	ph = (t_philo *)param;
	info = ph->info;
	if (info->nbr_to_eat > 0)
	{
		while (info->nbr_to_eat > ph->nbr_of_ate && !info->is_dead)
		{
			time = delta_time(ph->last_eat);
			if (time > info->time_to_die)
			{
				info->is_dead = 1;
				print_status(ph, info, "is dead!");
				return (NULL);
			}
		}
	}
	else
	{
		while (!info->is_dead)
		{
			time = delta_time(ph->last_eat);
			if (time > info->time_to_die)
			{
				info->is_dead = 1;
				print_status(ph, info, "is dead!");
				return (NULL);
			}
		}
	}
	return (NULL);
}

static void	routine(void *param)
{
	t_philo *ph;
	t_info	*info;

	ph = (t_philo *)param;
	info = ph->info;
	if (pthread_create(&ph->control, NULL, control, (void *)ph))
		exit(EXIT_FAILURE);
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
			if  (routine_exe(ph, info))
				break ;
	}
	exit(EXIT_SUCCESS);
}

int create_threads(t_info *info)
{
	int	i;

	i = 0;
	info->start_time = get_time();
	while (i < info->ph_nbr)
	{
		info->philos[i].pid = fork();
		if (info->philos[i].pid == -1)
		{
			while (--i >= 0)
				kill(info->philos[i].pid, SIGKILL);
			return (1);
		}
		else if (info->philos[i].pid == 0)
		{
			routine((void *)&info->philos[i]);
		}
		i++;
	}
	sem_wait(info->main_lock);
	return (0);
}