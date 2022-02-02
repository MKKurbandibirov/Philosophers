/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magomed <magomed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 12:55:03 by magomed           #+#    #+#             */
/*   Updated: 2022/02/02 13:26:20 by magomed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    taking_forks(t_philo *philo)
{
    pthread_mutex_lock(philo->l_f);
    pthread_mutex_lock(philo->r_f);
    pthread_mutex_lock(&philo->info->display);
    if (philo->stop != 1)
    {
        printf("%ld %d has taking a fork!\n",
            get_time() - philo->start_time, philo->id + 1);
        printf("%ld %d has taking a fork!\n",
            get_time() - philo->start_time, philo->id + 1);
    }
    pthread_mutex_unlock(&philo->info->display);
}

void    eating(t_philo *philo)
{
    pthread_mutex_lock(&philo->info->display);
    printf("%ld %d is eating!\n",
        get_time() - philo->start_time, philo->id + 1);
    pthread_mutex_unlock(&philo->info->display);
    philo->nbr_of_eat += 1;
    philo->last_eat = get_time();
    smart_sleep(philo->info->time_to_eat);
    pthread_mutex_unlock(philo->l_f);
    pthread_mutex_unlock(philo->r_f);
}

void    sleeping(t_philo *philo)
{
    pthread_mutex_lock(&philo->info->display);
    printf("%ld %d is sleeping!\n",
        get_time() - philo->start_time, philo->id + 1);
    pthread_mutex_unlock(&philo->info->display);
    smart_sleep(philo->info->time_to_sleep);
}

void    thinking(t_philo *philo)
{
    pthread_mutex_lock(&philo->info->display);
    printf("%ld %d is thinking!\n",
        get_time() - philo->start_time, philo->id + 1);
    pthread_mutex_unlock(&philo->info->display);
}