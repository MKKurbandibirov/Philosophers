/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 12:55:15 by magomed           #+#    #+#             */
/*   Updated: 2022/02/23 10:46:01 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	close_unlink(t_info *info)
{
	sem_close(info->forks);
	sem_unlink("forks");
	sem_close(info->write);
	sem_unlink("write");
	sem_close(info->main_lock);
	sem_unlink("main_lock");
	if (info->nbr_to_eat > 0)
	{
		sem_close(info->eat_enough);
		sem_unlink("eat_enough");
	}
}
