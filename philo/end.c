/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magomed <magomed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 11:33:33 by magomed           #+#    #+#             */
/*   Updated: 2022/02/02 11:49:18 by magomed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int join_threads(t_info *info)
{
    int i;

    i = -1;
    while (++i < info->ph_nmb)
    {
        if (pthread_join(info->threads[i], NULL))
            return (1);
    }
    return (0);
}

void    free_all(t_info *info)
{
    free(info->philos);
    free(info->threads);
    free(info->forks);
}

void    mutexes_destroy(t_info *info)
{
    int i;

    i = -1;
    while (++i < info->ph_nmb)
    {
        pthread_mutex_unlock(&info->forks[i]);
        pthread_mutex_destroy(&info->forks[i]);
    }
    pthread_mutex_unlock(&info->display);
    pthread_mutex_destroy(&info->display);
}