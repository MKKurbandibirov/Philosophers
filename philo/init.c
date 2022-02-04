/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 18:16:08 by magomed           #+#    #+#             */
/*   Updated: 2022/02/03 12:31:15 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo(t_info *info)
{
	int	i;

	i = -1;
	info->philos = malloc(sizeof(t_philo) * info->ph_nbr);
	if (!info->philos)
		return (1);
	while (++i < info->ph_nbr)
	{
		info->philos[i].id = i;
		info->philos[i].nbr_of_eat = 0;
		info->philos[i].last_eat = get_time();
		info->philos[i].limit_of_life = info->time_to_die;///llll
		info->philos[i].stop = 0;
		// info->philos[i].l_f = &info->forks[i % info->ph_nbr];
		// info->philos[i].r_f = &info->forks[(i + 1) % info->ph_nbr];
		info->philos[i].l_f = i;
		info->philos[i].r_f = (i + 1) % info->ph_nbr;
		info->philos[i].info = info;
	}
	return (0);
}

int	init_mutexes(t_info *info)
{
	int	i;

	i = -1;
	info->forks = malloc(sizeof(pthread_mutex_t) * info->ph_nbr);
	if (!info->forks)
		return (1);
	while (++i < info->ph_nbr)
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

	info->threads = malloc(sizeof(pthread_t) * info->ph_nbr);
	info->death_control = malloc(sizeof(pthread_t) * info->ph_nbr);
	if (!info->threads || !info->death_control)
		return (1);
	i = -1;
	while (++i < info->ph_nbr)
	{
		if (pthread_create(&info->threads[i], NULL, ph_process, &info->philos[i]))
			return (1);
		// usleep(1000);
	}
	return (0);
}

void	init_info(int ac, char **av, t_info *info)
{
	info->ph_nbr = ft_atoi(av[1]);
	info->time_to_die = (long)ft_atoi(av[2]);
	info->time_to_eat = (long)ft_atoi(av[3]);
	info->time_to_sleep = (long)ft_atoi(av[4]);
	info->dead = 0;
	info->nbr_to_eat = -1;
	if (ac == 6)
		info->nbr_to_eat = ft_atoi(av[5]);
}
