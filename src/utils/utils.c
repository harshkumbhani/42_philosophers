/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harsh <harsh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:21:14 by hkumbhan          #+#    #+#             */
/*   Updated: 2024/01/10 11:19:42 by harsh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(const char *str)
{
	long	i;
	long	num;
	long	sign;

	i = 0;
	num = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if ((str[i] == '+') || (str[i] == '-'))
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while ((char )str[i] >= '0' && (char)str[i] <= '9')
	{
		num = 10 * num + ((char)str[i] - '0');
		i++;
	}
	return (num * sign);
}

bool	check(char **av)
{
	int	i;
	int	j;

	j = 0;
	if (ft_atol(av[1]) == 0)
		return (false);
	while (av[++j])
	{
		i = 0;
		while (av[j][i])
		{
			if (av[j][i] < '0' || av[j][i] > '9')
				return (false);
			i++;
		}
		if (ft_atol(av[j]) > INT_MAX)
			return (false);
	}
	return (true);
}

void	print_args(t_arg *args)
{
	printf("Number of philos: %d\n", args->nb_philos);
	printf("Time to die: %d\n", args->time_to_die);
	printf("Time to sleep: %d\n", args->time_to_sleep);
	printf("Time to eat: %d\n", args->time_to_eat);
	printf("Number of times philos should eat: %d\n", args->eat_number);
}
