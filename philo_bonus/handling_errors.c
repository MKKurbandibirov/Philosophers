/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 09:20:58 by magomed           #+#    #+#             */
/*   Updated: 2022/02/21 15:37:10 by nfarfetc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

int	validation(int ac, char **av)
{
	int	i;

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

static int	spaces(const char *str)
{
	int	i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	long unsigned int	res;
	int					i;
	int					sign;

	i = 0;
	res = 0;
	sign = 1;
	i = spaces(str);
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
		if (res >= __LONG_MAX__ && sign == -1)
			return (0);
		if (res >= __LONG_MAX__ && sign == 1)
			return (-1);
	}
	return (res * sign);
}
