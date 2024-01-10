/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harsh <harsh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:39:27 by hkumbhan          #+#    #+#             */
/*   Updated: 2024/01/10 11:21:41 by harsh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_arguments(char **av, t_arg *args)
{
	args->nb_philos = (int)ft_atol(av[1]);
	args->time_to_die = (int)ft_atol(av[2]);
	args->time_to_eat = (int)ft_atol(av[3]);
	args->time_to_sleep = (int)ft_atol(av[4]);
	if (av[5] != NULL)
		args->eat_number = (int)ft_atol(av[5]);
	else
		args->eat_number = -1;
}

bool	init_philos(t_main *main_state, t_arg *arguments)
{
	int		i;
	t_philo	*philo;

	i = 1;
	philo = NULL;
	while (i <= arguments->nb_philos)
	{
		philo = ft_calloc(1, sizeof(t_philo));
		if (philo == NULL)
			return (false);
		philo->die_flag = false;
		philo->done_eat = false;
		philo->index = i;
		philo->times_eaten = 0;
		philo->time_last_eat = gettime();
		philo->start_time = &(main_state->start_time);
		philo->data = arguments;
		lst_add_back(main_state, philo);
		i++;
	}
	return (true);
}

bool	init(t_main *main_state, t_arg *args, int ac, char **av)
{
	if (ac != 5 && ac != 6)
		return (printf("Argument Error!\n"), false);
	if (check(av) == false)
		return (printf("Argument Error!\n"), false);
	init_arguments(av, args);
	if (init_philos(main_state, args) == false)
		return (printf("Alloc fail!\n"), false);
	if (init_mutex(main_state) == false)
		return (printf("Mutex init fail!\n"), false);
	if (init_threads(main_state) == false)
		return (printf("Threads init fail!\n"), false);
	return (true);
}
