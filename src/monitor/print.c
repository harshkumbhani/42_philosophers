/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkumbhan <hkumbhan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 16:23:30 by hkumbhan          #+#    #+#             */
/*   Updated: 2024/01/09 09:52:17 by hkumbhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_log(t_state state, t_philo *philo)
{
	static char	*str[] = {
		"has taken a fork", "is eating", "is sleeping",
		"is thinking", "died"
	};

	pthread_mutex_lock(philo->print_log);
	if (philo->die_flag == false)
	{
		printf("%lu %d %s\n", gettime() - *(philo->start_time), philo->index,
			str[state]);
	}
	pthread_mutex_unlock(philo->print_log);
}

void	handle_1_nb_of_philos(t_philo *philo)
{
	pthread_mutex_lock(&philo->m_philo);
	print_log(THINKING, philo);
	pthread_mutex_unlock(&philo->m_philo);
	printf("%lu %d %s\n", gettime() - *(philo->start_time), philo->index,
		"has taken a fork");
}
