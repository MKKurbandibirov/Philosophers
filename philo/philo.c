/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magomed <magomed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 09:21:29 by magomed           #+#    #+#             */
/*   Updated: 2022/02/07 13:01:38 by magomed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	if (create_threads(&info))
	{
		printf("threads error");
		return (1);
	}
	mutex_destroy(&info);
	free_info(&info);
	return (0);
}