/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkumbhan <hkumbhan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 15:20:53 by hkumbhan          #+#    #+#             */
/*   Updated: 2024/01/08 12:45:32 by hkumbhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	do_think(t_philo *philo)
{
	print_log(THINKING, philo);
}

void	do_sleep(t_philo *philo)
{
	print_log(SLEEPING, philo);
	ft_usleep(philo->data->time_to_sleep);
}

void	forks(t_philo *philo, int state)
{
	if (state == PICK_FORK)
	{
		usleep(500);
		pthread_mutex_lock(philo->left_f);
		pthread_mutex_lock(philo->right_f);
		print_log(FORK, philo);
		print_log(FORK, philo);
	}
	if (state == DROP_FORK)
	{
		pthread_mutex_unlock(philo->right_f);
		pthread_mutex_unlock(philo->left_f);
	}
}

void	do_eat(t_philo *philo)
{
	forks(philo, PICK_FORK);
	pthread_mutex_lock(&(philo->m_philo));
	philo->times_eaten++;
	philo->time_last_eat = gettime();
	print_log(EATING, philo);
	pthread_mutex_unlock(&(philo->m_philo));
	ft_usleep(philo->data->time_to_eat);
	forks(philo, DROP_FORK);
}

void *routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->print_log);
	pthread_mutex_unlock(philo->print_log);
	pthread_mutex_lock(&philo->m_philo);
	philo->time_last_eat = gettime();
	pthread_mutex_unlock(&philo->m_philo);
	if (philo->index % 2 == 0)
		do_eat(philo);
	while (philo->die_flag == false)
	{
		do_sleep(philo);
		do_think(philo);
		do_eat(philo);
	}
	return (NULL);
}
