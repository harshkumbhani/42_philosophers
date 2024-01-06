/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkumbhan <hkumbhan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 15:20:53 by hkumbhan          #+#    #+#             */
/*   Updated: 2024/01/06 13:34:22 by hkumbhan         ###   ########.fr       */
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

void	do_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->right_f);
	print_log(FORK, philo);
	pthread_mutex_lock(philo->left_f);
	print_log(FORK, philo);
	print_log(EATING, philo);
	pthread_mutex_lock(&(philo->m_philo));
	philo->times_eaten++;
	philo->time_last_eat = gettime();
	pthread_mutex_unlock(&(philo->m_philo));
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->left_f);
	pthread_mutex_unlock(philo->right_f);
}

void *routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->print_log);
	pthread_mutex_unlock(philo->print_log);
	while (1)
	{
		//printf("Hello %d\n", philo->index);
		if (philo->index % 2 == 0)
		{
			do_eat(philo);
			do_sleep(philo);
			do_think(philo);
		}
		else
		{
			do_sleep(philo);
			do_eat(philo);
			do_think(philo);
		}
	}
	return (NULL);
}
