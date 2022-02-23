/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 09:21:29 by magomed           #+#    #+#             */
/*   Updated: 2022/02/23 10:48:00 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	for_one_philo(t_info *info)
{
	info->start_time = get_time();
	print_status(&info->philos[0], info, "has taken a fork!");
	usleep(info->time_to_die * 1000);
	print_status(&info->philos[0], info, "is dead!");
	close_unlink(info);
	free(info->philos);
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (validation(argc, argv))
		return (1);
	if (create_info(argc, argv, &info))
		return (1);
	if (info.ph_nbr == 1)
	{
		for_one_philo(&info);
		return (0);
	}
	if (create_process(&info))
		return (1);
	close_unlink(&info);
	free(info.philos);
	return (0);
}
