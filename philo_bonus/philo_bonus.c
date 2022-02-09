/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magomed <magomed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 09:21:29 by magomed           #+#    #+#             */
/*   Updated: 2022/02/09 20:40:22 by magomed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	for_one_philo(t_info *info)
{
	info->start_time = get_time();
	print_status(&info->philos[0], info, "has taken a fork!");
	usleep(info->time_to_die * 1000);
	print_status(&info->philos[0], info, "is dead!");
	// mutex_destroy(info);
	free_info(info);
}

int main(int argc, char **argv)
{
	t_info  info;

	if (validation(argc, argv))
	{
		printf("valid error!");
		return (1);
	}
	if (create_info(argc, argv, &info))
	{
		printf("info error!");
		return (1);
	}
	if (info.ph_nbr == 1)
	{
		for_one_philo(&info);
		return (0);
	}
	if (create_threads(&info))
	{
		printf("threads error");
		return (1);
	}
	// mutex_destroy(&info);
	free_info(&info);
	return (0);
}