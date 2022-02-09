/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magomed <magomed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 12:55:15 by magomed           #+#    #+#             */
/*   Updated: 2022/02/09 20:40:03 by magomed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// void	mutex_destroy(t_info *info)
// {
// 	int	i;

// 	i = 0;
// 	while (i < info->ph_nbr)
// 	{
// 		pthread_mutex_destroy(&info->forks[i]);
// 		i++;
// 	}
// 	pthread_mutex_destroy(&info->write);
// }

void	free_info(t_info *info)
{
	free(info->forks);
	free(info->philos);
}