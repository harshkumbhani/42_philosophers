/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkumbhan <hkumbhan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:39:27 by hkumbhan          #+#    #+#             */
/*   Updated: 2024/01/06 16:44:14 by hkumbhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_args(t_arg *args)
{
	printf("Number of philos: %d\n", args->nb_philos);
	printf("Time to die: %d\n", args->time_to_die);
	printf("Time to sleep: %d\n", args->time_to_sleep);
	printf("Time to eat: %d\n", args->time_to_eat);
	printf("Number of times philos should eat: %d\n", args->eat_number);
}

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
	//print_args(args);
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
		philo->time_last_eat = 0;
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
		return (false);
	if (init_mutex(main_state) == false)
		return (false);
	if (init_threads(main_state) == false)
		return (false);
	return (true);
}
