/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 11:33:33 by magomed           #+#    #+#             */
/*   Updated: 2022/02/03 11:41:35 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	join_threads(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->ph_nbr)
	{
		if (pthread_join(info->threads[i], NULL))
			return (1);
	}
	if (info->dead)
		pthread_mutex_unlock(&info->display);
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
	int	i;

	i = -1;
	while (++i < info->ph_nbr)
	{
		pthread_mutex_unlock(&info->forks[i]);
		pthread_mutex_destroy(&info->forks[i]);
	}
}