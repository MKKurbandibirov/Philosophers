/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_info.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magomed <magomed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 09:25:53 by magomed           #+#    #+#             */
/*   Updated: 2022/02/07 17:05:07 by magomed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		info->philos[i].l_f = i;
		info->philos[i].r_f = (i + 1) % info->ph_nbr;
		info->philos[i].info = info;
		i++;
	}
	return (0);
}

static int	init_forks(t_info *info)
{
	int	i;

	i = 0;
	info->forks = malloc(sizeof(pthread_mutex_t) * info->ph_nbr);
	if (!info->forks)
		return (1);
	while (i < info->ph_nbr)
	{
		if (pthread_mutex_init(&info->forks[i], NULL))
		{
			printf("Couldn't init fork!");
			return (1);
		}
		i++;
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
	if (init_forks(info))
		return (1);
	if (pthread_mutex_init(&info->write, NULL))
		return (1);
	if (init_philos(info))
		return (1);
	return (0);
}