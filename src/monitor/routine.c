/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkumbhan <hkumbhan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 15:20:53 by hkumbhan          #+#    #+#             */
/*   Updated: 2024/01/09 09:22:22 by hkumbhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	do_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->m_philo);
	print_log(THINKING, philo);
	pthread_mutex_unlock(&philo->m_philo);
}

static void	do_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->m_philo);
	print_log(SLEEPING, philo);
	pthread_mutex_unlock(&philo->m_philo);
	ft_usleep(philo->data->time_to_sleep);
}

static void	forks(t_philo *philo, int state)
{
	if (state == PICK_FORK)
	{
		usleep(500);
		pthread_mutex_lock(philo->left_f);
		pthread_mutex_lock(philo->right_f);
		pthread_mutex_lock(&philo->m_philo);
		print_log(FORK, philo);
		print_log(FORK, philo);
		pthread_mutex_unlock(&philo->m_philo);
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
	pthread_mutex_lock(&(philo->m_philo));
	philo->times_eaten++;
	philo->time_last_eat = gettime();
	print_log(EATING, philo);
	pthread_mutex_unlock(&(philo->m_philo));
	ft_usleep(philo->data->time_to_eat);
	forks(philo, DROP_FORK);
}

void	handle_1_nb_of_philos(t_philo *philo)
{
	do_think(philo);
	printf("%lu %d %s\n", gettime() - *(philo->start_time), philo->index,
			"has taken a fork");
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
	pthread_mutex_lock(&philo->m_philo);
	while (philo->die_flag == false)
	{
		pthread_mutex_unlock(&philo->m_philo);
		do_sleep(philo);
		do_think(philo);
		do_eat(philo);
		pthread_mutex_lock(&philo->m_philo);
	}
	pthread_mutex_unlock(&philo->m_philo);
	return (NULL);
}
