/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 12:00:29 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/02/03 14:06:42 by nfarfetc         ###   ########.fr       */
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
	// long	cur_time;
	int	i;
	
	// cur_time = get_time();
	while (i < 10)
	{
		usleep(time * 100);
		i++;
	}
}



void	*ph_process(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	philo->last_eat = get_time();
	philo->start_time = get_time();
	pthread_create(&philo->info->death_control[philo->id],
		NULL, ph_death_controller, philo);
	pthread_detach(philo->info->death_control[philo->id]);
	while (!philo->info->dead)
	{
		if (philo->stop || philo->info->dead)
			return (NULL);
		thinking(philo);
		if (philo->stop || philo->info->dead)
			return (NULL);
		if (eating(philo))
		{
			usleep(1000 * philo->info->time_to_die);
			return (NULL);
		}
		if (philo->stop || philo->info->dead)
			return (NULL);
		sleeping(philo);
		if (philo->stop || philo->info->dead)
			return (NULL);
	}
	return (NULL);
}

void	*ph_death_controller(void *param)
{
	t_philo *philo;

	philo = (t_philo *)param;
	while (!philo->info->dead)
	{
		if (philo->info->ph_nbr != 1)
			pthread_mutex_lock(&philo->info->display);
		if (get_time() - philo->last_eat > philo->info->time_to_die && !philo->info->dead)
		{
			philo->info->dead = 1;
			printf("%ld %d is dead!\n",
				get_time() - philo->start_time, philo->id + 1);
			return (NULL);
		}
		if (philo->info->ph_nbr != 1)
			pthread_mutex_unlock(&philo->info->display);
		if (philo->nbr_of_eat == philo->info->nbr_to_eat)
		{
			philo->stop = 1;
			return (NULL);
		}
	}
	return (NULL);
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
	// for (int i = 0; i < info.ph_nbr; i++)
	// {
	// 	printf("%d\n", info.philos[i].id);
	// 	printf("%d\n", info.philos[i].l_f);
	// 	printf("%d\n", info.philos[i].r_f);
	// 	printf("%d\n", info.philos[i].stop);
	// 	printf("\n");
	// }
	if (init_threads(&info))
	{
		printf("Thread error!\n");
		return (1);
	}
	mutexes_destroy(&info);
	if (join_threads(&info))
	{
		printf("Thread join error!\n");
		return (1);
	}
	free_all(&info);
	return (0);
}
