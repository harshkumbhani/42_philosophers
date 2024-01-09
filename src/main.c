/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harsh <harsh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:37:05 by hkumbhan          #+#    #+#             */
/*   Updated: 2024/01/08 19:13:24 by harsh            ###   ########.fr       */
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
		if (philo->die_flag == false)
			philo->die_flag = true;
		philo = philo->next;
		if (philo == main_state->philos)
			break ;
	}
}

void	monitor(t_main *main_state)
{
	t_philo	*philo;
	int		philo_number;

	philo_number = 0;
	philo = main_state->philos;
	while (true)
	{
		if (philo_number == philo->data->nb_philos)
		{
			kill_all_philos(main_state);
			break ;
		}
		pthread_mutex_lock(&(philo->m_philo));
		if (gettime() - philo->time_last_eat >= philo->data->time_to_die)
		{
			pthread_mutex_unlock(&(philo->m_philo));
			pthread_mutex_lock(&philo->m_philo);
			print_log(DIED, philo);
			pthread_mutex_unlock(&philo->m_philo);
			pthread_mutex_lock(&main_state->print_log);
			kill_all_philos(main_state);
			pthread_mutex_unlock(&main_state->print_log);
			break ;
		}
		if (philo->done_eat == false && philo->times_eaten == philo->data->eat_number)
		{
			philo_number++;
			philo->done_eat = true;
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

// 1. Assign all values
// 2. Create mutexes
// 3. Lock the shared mutex
// 4. Create threads (threads will be stuck due to shared mutex)
// 5. After creating -> main thread will unlock shared
// 6. Loop through linked list and check if they should die
