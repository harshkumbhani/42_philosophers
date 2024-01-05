/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkumbhan <hkumbhan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 16:23:30 by hkumbhan          #+#    #+#             */
/*   Updated: 2024/01/05 17:48:19 by hkumbhan         ###   ########.fr       */
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
	//printf("Start: %lu\n", *(philo->start_time));
	//printf("diff: %lu\n", gettime() - *(philo->start_time));
	if (philo->die_flag == false)
		printf("%lu %d %s\n", gettime() - *(philo->start_time), philo->index,
			str[state]);
	pthread_mutex_unlock(philo->print_log);
}
