/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magomed <magomed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 12:00:29 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/02/02 14:01:12 by magomed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	tv;
	long 			ret;

	gettimeofday(&tv, NULL);
	ret = tv.tv_sec  * 1000;
	ret += tv.tv_usec / 1000;
	return (ret);
}

void	smart_sleep(long time)
{
	long	cur_time;
	
	cur_time = get_time();
	while (get_time() - cur_time < time)
		;
}



void	*ph_process(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	philo->last_eat = get_time();
	philo->start_time = get_time();
	while (!philo->info->dead)
	{
		if (philo->stop || philo->info->dead)
			return (NULL);
		taking_forks(philo);
		if (philo->stop || philo->info->dead)
			return (NULL);
		eating(philo);
		if (philo->stop || philo->info->dead)
			return (NULL);
		sleeping(philo);
		if (philo->stop || philo->info->dead)
			return (NULL);
			thinking(philo);
		if (philo->stop || philo->info->dead)
			return (NULL);
	}
	return (NULL);
}

void	*ph_death_controller(void *param)
{
	t_philo *philos;
	int		i;
	int		j;
	long	cur_time;

	philos = (t_philo *)param;
	while (philos[0].stop == 0)
	{
		i = -1;
		while (++i < philos[0].info->ph_nbr)
		{
			cur_time = get_time();
			if (cur_time - philos[i].last_eat > philos[i].limit_of_life)
			{
				pthread_mutex_lock(&philos[i].info->display);
				philos[i].info->dead = 1;
				printf("%ld %d is dead!\n",
        			get_time() - philos[i].start_time, philos[i].id + 1);
				pthread_mutex_unlock(&philos[i].info->display);
				return (NULL);
			}
			if (philos[i].nbr_of_eat >= philos[i].info->nbr_to_eat)
			{
				j = -1;
				while (++j < philos[i].info->ph_nbr)
					philos[j].stop = 1;
				return (NULL);
			}
		}
	}
}

int	main(int ac, char **av)
{
	t_info	info;
	int		i;

	if (validation(ac, av))
		return (1);
	init_info(ac, av, &info);
	if (init_philo(&info))
	{
		printf("Malloc error!\n");
		return (1);
	}
	if (init_mutexes(&info))
	{
		printf("Mutex error!\n");
		return (1);
	}
	if (init_threads(&info))
	{
		printf("Thread error!\n");
		return (1);
	}
	if (join_threads(&info))
	{
		printf("Thread join error!\n");
		return (1);
	}
	mutexes_destroy(&info);
	free_all(&info);
	return (0);
}
