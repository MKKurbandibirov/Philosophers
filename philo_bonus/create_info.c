/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_info.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 09:25:53 by magomed           #+#    #+#             */
/*   Updated: 2022/02/23 10:41:03 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	init_philos(t_info *info)
{
	int	i;

	i = 0;
	info->philos = malloc(sizeof(t_philo) * info->ph_nbr);
	if (!info->philos)
		return (1);
	while (i < info->ph_nbr)
	{
		info->philos[i].id = i + 1;
		info->philos[i].last_eat = 0;
		info->philos[i].nbr_of_ate = 0;
		info->philos[i].info = info;
		i++;
	}
	return (0);
}

static void	init_sem(t_info *info)
{
	sem_unlink("forks");
	sem_unlink("write");
	sem_unlink("main_lock");
	info->forks = sem_open("forks", O_CREAT | O_EXCL, S_IRWXU, info->ph_nbr);
	info->write = sem_open("write", O_CREAT | O_EXCL, S_IRWXU, 1);
	info->main_lock = sem_open("main_lock", O_CREAT | O_EXCL, S_IRWXU, 0);
	if (info->nbr_to_eat > 0)
	{
		sem_unlink("eat_enough");
		info->eat_enough = sem_open("eat_enough", O_CREAT | O_EXCL, S_IRWXU, 0);
	}
}

static void	*eat_control(void *param)
{
	t_info	*info;
	int		i;

	info = (t_info *)param;
	i = -1;
	sem_wait(info->write);
	while (++i < info->ph_nbr)
	{
		sem_post(info->write);
		sem_wait(info->eat_enough);
		sem_wait(info->write);
	}
	sem_post(info->main_lock);
	return (NULL);
}

static int	init_eat_control(t_info *info)
{
	if (info->nbr_to_eat > 0)
	{
		if (pthread_create(&info->eating_check, NULL, &eat_control, info))
			return (1);
		pthread_detach(info->eating_check);
	}
	return (0);
}

int	create_info(int ac, char **av, t_info *info)
{
	info->ph_nbr = ft_atoi(av[1]);
	info->time_to_die = ft_atoi(av[2]);
	info->time_to_eat = ft_atoi(av[3]);
	info->time_to_sleep = ft_atoi(av[4]);
	info->nbr_to_eat = -1;
	if (ac == 6)
		info->nbr_to_eat = ft_atoi(av[5]);
	info->is_dead = 0;
	init_sem(info);
	if (init_philos(info))
		return (1);
	if (init_eat_control(info))
		return (1);
	return (0);
}
