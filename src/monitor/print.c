/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harsh <harsh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 16:23:30 by hkumbhan          #+#    #+#             */
/*   Updated: 2024/01/08 18:49:34 by harsh            ###   ########.fr       */
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
