/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 12:55:03 by magomed           #+#    #+#             */
/*   Updated: 2022/02/03 14:10:20 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	taking_forks(t_philo *philo)
// {
// 	pthread_mutex_lock(philo->l_f);
// 	pthread_mutex_lock(philo->r_f);
// 	pthread_mutex_lock(&philo->info->display);
// 	if (philo->stop != 1)
// 	{
// 		printf("%ld %d has taking a fork!\n",
// 			get_time() - philo->start_time, philo->id + 1);
// 		printf("%ld %d has taking a fork!\n",
// 			get_time() - philo->start_time, philo->id + 1);
// 	}
// }

int	eating(t_philo *philo)
{
	// pthread_mutex_lock(philo->l_f);
	// pthread_mutex_lock(philo->r_f);
	pthread_mutex_lock(&philo->info->forks[philo->l_f]);
	pthread_mutex_lock(&philo->info->forks[philo->r_f]);
	pthread_mutex_lock(&philo->info->display);
	if (philo->stop != 1)
	{
		printf("%ld %d has taking a fork! %d\n",
			get_time() - philo->start_time, philo->id + 1, philo->l_f);
		if (philo->info->ph_nbr == 1)
			return (1);
		printf("%ld %d has taking a fork!%d\n",
			get_time() - philo->start_time, philo->id + 1, philo->r_f);
	}
	printf("%ld %d is eating!\n",
		get_time() - philo->start_time, philo->id + 1);
	pthread_mutex_unlock(&philo->info->display);
	philo->nbr_of_eat += 1;
	philo->last_eat = get_time();
	usleep(philo->info->time_to_eat * 1000);
	smart_sleep(philo->info->time_to_eat);
	pthread_mutex_unlock(&philo->info->forks[philo->r_f]);
	pthread_mutex_unlock(&philo->info->forks[philo->l_f]);
	// pthread_mutex_unlock(philo->l_f);
	// pthread_mutex_unlock(philo->r_f);
	return (0);
}

void    sleeping(t_philo *philo)
{
    pthread_mutex_lock(&philo->info->display);
    printf("%ld %d is sleeping!\n",
        get_time() - philo->start_time, philo->id + 1);
    pthread_mutex_unlock(&philo->info->display);
    usleep (philo->info->time_to_sleep * 1000);
}

void    thinking(t_philo *philo)
{
    pthread_mutex_lock(&philo->info->display);
    printf("%ld %d is thinking!\n",
        get_time() - philo->start_time, philo->id + 1);
    pthread_mutex_unlock(&philo->info->display);
}