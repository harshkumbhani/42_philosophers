/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harsh <harsh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 15:20:53 by hkumbhan          #+#    #+#             */
/*   Updated: 2024/05/05 15:30:28 by harsh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	do_think(t_philo *philo)
{
	print_log(THINKING, philo);
}

static void	do_sleep(t_philo *philo)
{
	print_log(SLEEPING, philo);
	ft_usleep(philo->data->time_to_sleep);
}

static void	forks(t_philo *philo, int state)
{
	if (state == PICK_FORK)
	{
		usleep(500);
		if (philo->index % 2 == 0)
		{
			pthread_mutex_lock(philo->left_f);
			pthread_mutex_lock(philo->right_f);
		}
		else
		{
			pthread_mutex_lock(philo->right_f);
			pthread_mutex_lock(philo->left_f);
		}
		print_log(FORK, philo);
		print_log(FORK, philo);
	}
	if (state == DROP_FORK)
	{
		pthread_mutex_unlock(philo->right_f);
		pthread_mutex_unlock(philo->left_f);
	}
}

static void	do_eat(t_philo *philo)
{
	forks(philo, PICK_FORK);
	pthread_mutex_lock(&philo->m_philo);
	philo->time_last_eat = gettime();
	philo->times_eaten++;
	print_log(EATING, philo);
	pthread_mutex_unlock(&philo->m_philo);
	ft_usleep(philo->data->time_to_eat);
	forks(philo, DROP_FORK);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->print_log);
	pthread_mutex_unlock(philo->print_log);
	if (philo->data->nb_philos == 1)
	{
		handle_1_nb_of_philos(philo);
		return (NULL);
	}
	if (philo->index % 2 == 0)
		do_eat(philo);
	pthread_mutex_lock(philo->print_log);
	while (philo->die_flag == false && philo->done_eat == false)
	{
		pthread_mutex_unlock(philo->print_log);
		do_sleep(philo);
		do_think(philo);
		do_eat(philo);
		pthread_mutex_lock(philo->print_log);
	}
	pthread_mutex_unlock(philo->print_log);
	return (NULL);
}
