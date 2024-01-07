/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkumbhan <hkumbhan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:37:05 by hkumbhan          #+#    #+#             */
/*   Updated: 2024/01/07 09:38:52 by hkumbhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	monitor(t_main *main_state)
{
	
}

int	main(int argc, char **argv)
{
	t_main	main_state;
	t_arg	arguments;
	t_philo	*philo;

	main_state = (t_main){};
	arguments = (t_arg){};
	philo = main_state.philos;
	if (init(&main_state, &arguments, argc, argv) == false)
		return (EXIT_FAILURE);
	main_state.start_time = gettime();
	pthread_mutex_unlock(&main_state.print_log);
	while (1)
	{
		pthread_join(philo->thread, NULL);
		philo = philo->next;
		if (philo == main_state.philos)
			break ;
	}
	return (EXIT_SUCCESS);
}

// 1. Assign all values
// 2. Create mutexes
// 3. Lock the shared mutex
// 4. Create threads (threads will be stuck due to shared mutex)
// 5. After creating -> main thread will unlock shared
// 6. Loop through linked list and check if they should die
