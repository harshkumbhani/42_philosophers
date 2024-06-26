/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harsh <harsh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:37:05 by hkumbhan          #+#    #+#             */
/*   Updated: 2024/05/05 14:52:33 by harsh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	join_threads(t_main *main_state)
{
	t_philo	*philo;

	philo = main_state->philos;
	while (1)
	{
		pthread_join(philo->thread, NULL);
		philo = philo->next;
		if (philo == main_state->philos)
			break ;
	}
}

int	main(int argc, char **argv)
{
	t_main	main_state;
	t_arg	arguments;

	main_state = (t_main){};
	arguments = (t_arg){};
	if (init(&main_state, &arguments, argc, argv) == false)
	{
		free_everything(&main_state);
		return (EXIT_FAILURE);
	}
	main_state.start_time = gettime();
	pthread_mutex_unlock(&main_state.print_log);
	monitor(&main_state);
	join_threads(&main_state);
	free_everything(&main_state);
	return (EXIT_SUCCESS);
}
