/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 12:00:29 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/01/27 16:47:49 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	forks_check(t_philos *ph)
{
	if (ph->cur != ph->ph_nmb - 1 && ph->forks[ph->cur] == 0
		&& ph->forks[ph->cur + 1] == 0)
	{
		ph->forks[ph->cur] = 1;
		printf("%6zu %d has taken a fork!\n", ph->time[ph->cur], ph->cur + 1);
		ph->forks[ph->cur + 1] = 1;
		printf("%6zu %d has taken a fork!\n", ph->time[ph->cur], ph->cur + 1);
		printf("%6zu %d is eating!\n", ph->time[ph->cur], ph->cur + 1);
		ph->is_eat[ph->cur] = 1;
		ph->time[ph->cur] += ph->time_to_eat;
		return (1);
	}
	if (ph->cur == ph->ph_nmb - 1 && ph->forks[ph->cur] == 0
		&& ph->forks[0] == 0)
	{
		ph->forks[ph->cur] = 1;
		printf("%6zu %d has taken a fork!\n", ph->time[ph->cur], ph->cur + 1);
		ph->forks[ph->cur + 1] = 1;
		printf("%6zu %d has taken a fork!\n", ph->time[ph->cur], ph->cur + 1);
		printf("%6zu %d is eating!\n", ph->time[ph->cur], ph->cur + 1);
		ph->is_eat[ph->cur] = 1;
		ph->time[ph->cur] += ph->time_to_eat;
		return (1);
	}
	return (0);
}

void	*thread_func1(void *philos)
{
	t_philos	*ph;

	ph = (t_philos *) philos;
	pthread_mutex_lock(&ph->mutex[ph->cur]);
	if (!forks_check(ph))
	{
		printf("%6zu %d is thinking!\n", ph->time[ph->cur], ph->cur + 1);
		ph->time[ph->cur] += ph->time_to_eat;
	}
	pthread_mutex_unlock(&ph->mutex[ph->cur]);
	return (NULL);
}

void	*thread_func2(void *philos)
{
	t_philos	*ph;

	ph = (t_philos *) philos;
	pthread_mutex_lock(&ph->mutex[ph->cur]);
	if (ph->is_eat[ph->cur])
	{
		printf("%6zu %d is sleeping!\n", ph->time[ph->cur], ph->cur + 1);
		ph->time[ph->cur] += ph->time_to_sleep;
	}
	else if (!ph->is_eat[ph->cur])
		forks_check(ph);
	pthread_mutex_unlock(&ph->mutex[ph->cur]);
	return (NULL);
}

int	main(int ac, char **av)
{
	t_philos	philos;
	pthread_t	*threads;
	int			check;

	if (ac == 5)
	{
		philos.ph_nmb = ft_atoi(av[1]);
		philos.time_to_die = (size_t)ft_atoi(av[2]);
		philos.time_to_eat = (size_t)ft_atoi(av[3]);
		philos.time_to_sleep = (size_t)ft_atoi(av[4]);
		threads = (pthread_t *)malloc(sizeof(pthread_t) * philos.ph_nmb);
		if (!threads)
			return (1);

		philos.mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * philos.ph_nmb);
		if (!philos.mutex)
			return (1);
		philos.cur = -1;
		while (++philos.cur < philos.ph_nmb)
			pthread_mutex_init(&philos.mutex[philos.cur], NULL);

		philos.is_eat = (int *)malloc(sizeof(int) * philos.ph_nmb);
		if (!philos.is_eat)
			return (1);
		philos.cur = -1;
		while (++philos.cur < philos.ph_nmb)
			philos.is_eat[philos.cur] = 0;

		philos.is_sleep = (int *)malloc(sizeof(int) * philos.ph_nmb);
		if (!philos.is_sleep)
			return (1);
		philos.cur = -1;
		while (++philos.cur < philos.ph_nmb)
			philos.is_sleep[philos.cur] = 0;

		philos.time = (size_t *)malloc(sizeof(size_t) * philos.ph_nmb);
		if (!philos.time)
			return (1);
		philos.cur = -1;
		while (++philos.cur < philos.ph_nmb)
			philos.time[philos.cur] = 0;

		philos.forks = (int *)malloc(sizeof(int) * philos.ph_nmb);
		if (!philos.forks)
			return (1);
		philos.cur = -1;
		while (++philos.cur < philos.ph_nmb)
			philos.forks[philos.cur] = 0;
			
//----------------------------------threads1---------------------------------

		philos.cur = -1;
		while (++philos.cur < philos.ph_nmb)
		{
			check = pthread_create(&threads[philos.cur], NULL, thread_func1, &philos);
			usleep(100);
			if (check != 0)
				printf("Error: could not create thread!");
		}
		philos.cur = -1;
		while (++philos.cur < philos.ph_nmb)
		{
			check = pthread_join(threads[philos.cur], NULL);
			if (check != 0)
				printf("Error: could not join thread!");
		}

//-----------------------------------threads2---------------------------------
		philos.cur = -1;
		while (++philos.cur < philos.ph_nmb)
		{
			check = pthread_create(&threads[philos.cur], NULL, thread_func2, &philos);
			usleep(100);
			if (check != 0)
				printf("Error: could not create thread!");
		}
		philos.cur = -1;
		while (++philos.cur < philos.ph_nmb)
		{
			check = pthread_join(threads[philos.cur], NULL);
			if (check != 0)
				printf("Error: could not join thread!");
		}

	}
	return (0);
}
