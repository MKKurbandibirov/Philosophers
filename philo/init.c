/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magomed <magomed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 18:16:08 by magomed           #+#    #+#             */
/*   Updated: 2022/02/02 11:25:46 by magomed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo(t_info *info)
{
	int	i;

	i = -1;
	info->philos = malloc(sizeof(t_philo) * info->ph_nmb);
	if (!info->philos)
		return (1);
	while (++i < info->ph_nmb)
	{
		info->philos[i].id = i;
		//------//
		info->philos[i].last_eat = get_time();
		info->philos[i].limit_of_life = info->time_to_die;///llll
		info->philos[i].stop = 0;
		info->philos[i].l_f = &info->forks[info->philos[i].id];
		info->philos[i].r_f = &info->forks[(info->philos[i].id + 1) % info->ph_nmb];
		info->philos[i].info = info;
	}
	return (0);
}

int	init_mutexes(t_info *info)
{
	int	i;

	i = -1;
	info->forks = malloc(sizeof(pthread_mutex_t) * info->ph_nmb);
	if (!info->forks)
		return (1);
	while (++i < info->ph_nmb)
	{
		if (pthread_mutex_init(&info->forks[i], NULL))
			return (1);
	}
	pthread_mutex_init(&info->display, NULL);
	return (0);
}

int	init_threads(t_info *info)
{
	int	i;

	info->threads = malloc(sizeof(pthread_t) * info->ph_nmb);
	i = -1;
	while (++i < info->ph_nmb)
	{
		if (pthread_create(&info->threads[i], NULL, ph_process, &info->philos[i]))
			return (1);
	}
	pthread_create(&info->death_control, NULL, ph_death_controller, &info->philos);
	pthread_join(info->death_control, NULL);
}

void	init_info(int ac, char **av, t_info *info)
{
	info->ph_nmb = ft_atoi(av[1]);
	info->time_to_die = (long)ft_atoi(av[2]);
	info->time_to_eat = (long)ft_atoi(av[3]);
	info->time_to_sleep = (long)ft_atoi(av[4]);
	info->dead = 0;
	info->nmb_to_eat = -1;
	if (ac == 6)
		info->nmb_to_eat = ft_atoi(av[5]);
}
