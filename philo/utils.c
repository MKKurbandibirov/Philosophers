/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magomed <magomed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 17:48:50 by magomed           #+#    #+#             */
/*   Updated: 2022/02/01 18:15:25 by magomed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_digit(char *str)
{
	while (*str)
	{
		if (!('0' <= *str && *str <= '9'))
			return (0);
		str++;
	}
	return (1);
}

int validation(int ac, char **av)
{
    int i;

    if (ac < 5 || ac > 6)
    {
        printf("Wrong exeutable pattern!\n");
        return (1);
    }
    i = 1;
    while (i < ac)
    {
        if (!is_digit(av[i]) || ft_atoi(av[i]) < 1)
        {
            printf("Incorrect argument!\n");
            return (1);
        }
        i++;
    }
    return (0);
}