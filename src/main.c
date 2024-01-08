/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkumbhan <hkumbhan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:37:05 by hkumbhan          #+#    #+#             */
/*   Updated: 2024/01/08 12:39:28 by hkumbhan         ###   ########.fr       */
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

static void	kill_all_philos(t_main *main_state)
{
	t_philo	*philo;

	philo = main_state->philos;
	while (true)
	{
		pthread_mutex_lock(&philo->m_philo);
		if (philo->die_flag == false)
			philo->die_flag = true;
		pthread_mutex_unlock(&(philo->m_philo));
		philo = philo->next;
		if (philo == main_state->philos)
			break ;
	}
	ft_usleep(main_state->philos->data->time_to_eat + 
			main_state->philos->data->time_to_sleep + 10);
}

void	monitor(t_main *main_state)
{
	t_philo	*philo;

	philo = main_state->philos;
	while (true)
	{
		pthread_mutex_lock(&(philo->m_philo));
		if (gettime() - philo->time_last_eat >= philo->data->time_to_die)
		{
			print_log(DIED, philo);
			pthread_mutex_unlock(&(philo->m_philo));
			kill_all_philos(main_state);
			break ;
		}
		pthread_mutex_unlock(&(philo->m_philo));
		philo = philo->next;
	}
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
	monitor(&main_state);
	join_threads(&main_state);
	return (EXIT_SUCCESS);
}

// 1. Assign all values
// 2. Create mutexes
// 3. Lock the shared mutex
// 4. Create threads (threads will be stuck due to shared mutex)
// 5. After creating -> main thread will unlock shared
// 6. Loop through linked list and check if they should die
