/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 12:00:29 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/01/30 17:43:38 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_time(int start)
{
	struct timeval	tv;
	long 			ret;

	gettimeofday(&tv, NULL);
	ret = (tv.tv_sec % 1000000) * 1000;
	ret += tv.tv_usec / 1000;
	return (ret - (size_t)start);
}

void	display_status(t_info *info, char *status, int id)
{
	pthread_mutex_lock(&info->display);
	printf(status, get_time(info->start_time), id);
	pthread_mutex_unlock(&info->display);
}

void	smart_sleep(t_info *info, size_t time)
{
	size_t	cur_time;
	
	cur_time = get_time(info->start_time);
	while (get_time(info->start_time) - cur_time < time)
		;
}

void	*thread_func1(void *param)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = (t_philo *) param;
	while(1)
	{
		// if ((long)(get_time(philo->info->start_time) - philo->info->time_to_die) < philo->last_eat)
		// {
		// 	display_status(philo->info, "%6lu %d is dead!\n", philo->id);
		// 	pthread_mutex_lock(&philo->info->display);
			
		// 	break ;
		// }
		display_status(philo->info, "%6lu %d is thinking!\n", philo->id);
		pthread_mutex_lock(&philo->info->philos[(philo->id % philo->info->ph_nmb) - 1].fork);
		display_status(philo->info, "%6lu %d has taken a fork!\n", philo->id);
		pthread_mutex_lock(&philo->info->philos[((philo->id + 1) % philo->info->ph_nmb) - 1].fork);
		display_status(philo->info, "%6lu %d has taken a fork!\n", philo->id);
		display_status(philo->info, "%6lu %d is eating!\n", philo->id);
		philo->last_eat = get_time(philo->info->start_time);
		smart_sleep(philo->info, philo->info->time_to_eat);
		pthread_mutex_unlock(&philo->info->philos[(philo->id % philo->info->ph_nmb) - 1].fork);
		pthread_mutex_unlock(&philo->info->philos[((philo->id + 1) % philo->info->ph_nmb) - 1].fork);
		if (++i == philo->info->nmb_to_eat)
		{
			philo->info->count_of_eat++;
			break ;
		}
		display_status(philo->info, "%6lu %d is sleeping!\n", philo->id);
		smart_sleep(philo->info, philo->info->time_to_sleep);
	}
	return (NULL);
}

void	*death_monitoring(void *param)
{
	t_info	*info;
	int		i;
	int		is_dead;
	
	info = (t_info *)param;
	is_dead = 1;
	// info->count_of_eat != info->ph_nmb && 
	while (is_dead)
	{
		i = 0;
		while (i < info->ph_nmb)
		{
			if ((long)(get_time(info->start_time) - info->time_to_die) >= info->philos[i].last_eat)
			{
				is_dead = 0;
				printf(" HAHAHAHAHAHHAHAHHA  %d HAHAHAHAHAHHAHAH\n", (long)(get_time(info->start_time) - info->time_to_die) >= info->philos[i].last_eat);
				printf(" HAHAHAHAHAHHAHAHHA  %ld HAHAHAHAHAHHAHAH\n", info->start_time);
				printf(" HAHAHAHAHAHHAHAHHA  %ld HAHAHAHAHAHHAHAH\n", get_time(info->start_time));
				printf(" HAHAHAHAHAHHAHAHHA  %ld HAHAHAHAHAHHAHAH\n", info->time_to_die);
				printf(" HAHAHAHAHAHHAHAHHA  %ld HAHAHAHAHAHHAHAH\n", info->philos[i].last_eat);
				display_status(info, "%6lu %d is dead!\n", i);
				break ;
			}
			i++;
		}
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_info	info;
	int		i;

	if (ac == 5 || ac == 6)
	{
		info.ph_nmb = ft_atoi(av[1]);
		info.time_to_die = (size_t)ft_atoi(av[2]);
		info.time_to_eat = (size_t)ft_atoi(av[3]);
		info.time_to_sleep = (size_t)ft_atoi(av[4]);
		info.start_time = get_time(0);
		if (ac == 6)
		{
			info.nmb_to_eat = ft_atoi(av[5]);
			info.count_of_eat = 0;
		}
		else
		{
			info.nmb_to_eat = -1;
			info.count_of_eat = -1;
		}
		info.philos = (t_philo *)malloc(sizeof(t_philo) * info.ph_nmb);
		if (!info.philos)
			return (1);
		pthread_mutex_init(&info.display, NULL);
		i = -1;
		while (++i < info.ph_nmb)
		{
			info.philos[i].id = i + 1;
			info.philos[i].last_eat = get_time(info.start_time);
			info.philos[i].info = &info;
			pthread_mutex_init(&info.philos[i].fork, NULL);
			if (pthread_create(&info.philos[i].thread, NULL, thread_func1, &info.philos[i]) != 0)
				printf("Error: could not create thread!");
			usleep(100);
		}
		i = -1;
		while (++i < info.ph_nmb)
		{
			if (pthread_join(info.philos[i].thread, NULL) != 0)
				printf("Error: could not join thread!");
		}
		
		// pthread_create(&info.death_control, NULL, death_monitoring, &info);
		
		// pthread_join(info.death_control, NULL);
		
		// i = -1;
		// while (++i < info.ph_nmb)
		// {
		// 	if (pthread_join(info.philos[i].thread, NULL) != 0)
		// 		printf("Error: could not join thread!");
		// }
	}
	return (0);
}
