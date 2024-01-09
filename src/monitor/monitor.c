/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkumbhan <hkumbhan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 09:53:51 by hkumbhan          #+#    #+#             */
/*   Updated: 2024/01/09 12:09:01 by hkumbhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

static void	kill_the_philo(t_main *main_state, t_philo *philo)
{
	pthread_mutex_unlock(&(philo->m_philo));
	pthread_mutex_lock(&philo->m_philo);
	print_log(DIED, philo);
	pthread_mutex_unlock(&philo->m_philo);
	pthread_mutex_lock(&main_state->print_log);
	kill_all_philos(main_state);
	pthread_mutex_unlock(&main_state->print_log);
}

static bool	check_philo_number(t_philo *philo, int philo_number,
		t_main *main_state)
{
	if (philo_number == philo->data->nb_philos)
	{
		kill_all_philos(main_state);
		return (true);
	}
	return (false);
}

void	monitor(t_main *main_state)
{
	t_philo	*philo;
	int		philo_number;

	philo_number = 0;
	philo = main_state->philos;
	while (true)
	{
		if (check_philo_number(philo, philo_number, main_state) == true)
			break ;
		pthread_mutex_lock(&(philo->m_philo));
		if (gettime() - philo->time_last_eat >= philo->data->time_to_die)
		{
			kill_the_philo(main_state, philo);
			break ;
		}
		if (philo->done_eat == false
			&& philo->times_eaten == philo->data->eat_number)
		{
			philo->done_eat = true;
			philo_number++;
		}
		pthread_mutex_unlock(&(philo->m_philo));
		philo = philo->next;
	}
}
