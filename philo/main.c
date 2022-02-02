/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magomed <magomed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 12:00:29 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/02/02 11:51:10 by magomed          ###   ########.fr       */
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

// void	display_status(t_info *info, char *status, int id)
// {
// 	pthread_mutex_lock(&info->display);
// 	printf(status, get_time(info->start_time), id);
// 	pthread_mutex_unlock(&info->display);
// }

// void	smart_sleep(t_info *info, long time)
// {
// 	long	cur_time;
	
// 	cur_time = get_time(info->start_time);
// 	while (get_time(info->start_time) - cur_time < time)
// 		;
// }

// void	*thread_func1(void *param)
// {
// 	t_philo	*philo;
// 	int		i;

// 	i = 0;
// 	philo = (t_philo *) param;
// 	while(1)
// 	{
// 		// if ((long)(get_time(philo->info->start_time) - philo->info->time_to_die) < philo->last_eat)
// 		// {
// 		// 	display_status(philo->info, "%6lu %d is dead!\n", philo->id);
// 		// 	pthread_mutex_lock(&philo->info->display);
			
// 		// 	break ;
// 		// }
// 		display_status(philo->info, "%6lu %d is thinking!\n", philo->id);
// 		pthread_mutex_lock(&philo->info->philos[(philo->id % philo->info->ph_nmb) - 1].fork);
// 		display_status(philo->info, "%6lu %d has taken a fork!\n", philo->id);
// 		pthread_mutex_lock(&philo->info->philos[((philo->id + 1) % philo->info->ph_nmb) - 1].fork);
// 		display_status(philo->info, "%6lu %d has taken a fork!\n", philo->id);
// 		display_status(philo->info, "%6lu %d is eating!\n", philo->id);
// 		philo->last_eat = get_time(philo->info->start_time);
// 		smart_sleep(philo->info, philo->info->time_to_eat);
// 		pthread_mutex_unlock(&philo->info->philos[(philo->id % philo->info->ph_nmb) - 1].fork);
// 		pthread_mutex_unlock(&philo->info->philos[((philo->id + 1) % philo->info->ph_nmb) - 1].fork);
// 		if (++i == philo->info->nmb_to_eat)
// 		{
// 			philo->info->count_of_eat++;
// 			break ;
// 		}
// 		display_status(philo->info, "%6lu %d is sleeping!\n", philo->id);
// 		smart_sleep(philo->info, philo->info->time_to_sleep);
// 	}
// 	return (NULL);
// }

// void	*death_monitoring(void *param)
// {
// 	t_info	*info;
// 	int		i;
// 	int		is_dead;
	
// 	info = (t_info *)param;
// 	is_dead = 1;
// 	// info->count_of_eat != info->ph_nmb && 
// 	while (is_dead)
// 	{
// 		i = 0;
// 		while (i < info->ph_nmb)
// 		{
// 			if (get_time(info->start_time) - info->time_to_die >= info->philos[i].last_eat)
// 			{
// 				is_dead = 0;
// 				display_status(info, "%6lu %d is dead!\n", i);
// 				break ;
// 			}
// 			i++;
// 		}
// 	}
// 	return (NULL);
// }

void	*ph_process(void *param)
{
	
}

void	*ph_death_controller(void *param)
{
	
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
