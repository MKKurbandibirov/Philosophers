/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magomed <magomed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 12:55:15 by magomed           #+#    #+#             */
/*   Updated: 2022/02/12 10:12:01 by magomed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	close_destroy(t_info *info)
{
	sem_close(info->forks);
	sem_destroy(info->forks);
	sem_close(info->write);
	sem_destroy(info->write);
	sem_close(info->main_lock);
	sem_destroy(info->main_lock);
}
