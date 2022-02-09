/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_info.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magomed <magomed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 09:25:53 by magomed           #+#    #+#             */
/*   Updated: 2022/02/09 20:27:22 by magomed          ###   ########.fr       */
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

static int	init_forks(t_info *info)
{
	sem_unlink("forks");
	sem_unlink("write");
	info->forks = sem_open("forks", O_CREAT | O_EXCL, S_IRWXU, info->ph_nbr);
	info->write = sem_open("write", O_CREAT | O_EXCL, S_IRWXU, 1);
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
	if (init_forks(info))
		return (1);
	if (init_philos(info))
		return (1);
	return (0);
}