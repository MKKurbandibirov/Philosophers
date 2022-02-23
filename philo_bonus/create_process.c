/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 09:47:07 by magomed           #+#    #+#             */
/*   Updated: 2022/02/23 10:50:26 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	*control(void *param)
{
	t_philo		*ph;
	t_info		*info;

	ph = (t_philo *)param;
	info = ph->info;
	while (!info->is_dead)
	{
		if (check_death(ph, info))
			break ;
	}
	sem_post(info->main_lock);
	sem_wait(info->write);
	exit(EXIT_FAILURE);
}

static void	routine(t_philo *ph, t_info *info)
{
	if (pthread_create(&ph->control, NULL, control, (void *)ph))
		exit(EXIT_FAILURE);
	pthread_detach(ph->control);
	while (!info->is_dead)
	{
		if (eating(ph, info))
			break ;
		sleeping(ph, info);
		thinking(ph, info);
	}
	exit(EXIT_SUCCESS);
}

int	create_process(t_info *info)
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
			routine(&info->philos[i], info);
		i++;
	}
	sem_wait(info->main_lock);
	return (0);
}
