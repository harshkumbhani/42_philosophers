/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_and_mutexes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkumbhan <hkumbhan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 17:15:58 by hkumbhan          #+#    #+#             */
/*   Updated: 2024/01/05 17:55:34 by hkumbhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	init_mutex(t_main *main_state)
{
	t_philo	*temp;

	temp = main_state->philos;
	if (pthread_mutex_init(&main_state->print_log, NULL) != 0)
		return (false);
	while (1)
	{
		temp->right_f = ft_calloc(1, sizeof(pthread_mutex_t));
		if (pthread_mutex_init(temp->right_f, NULL) != 0)
			return (false);
		if (pthread_mutex_init(&(temp->m_philo), NULL) != 0)
			return (false);
		temp->print_log = &(main_state->print_log);
		temp->start_time = &(main_state->start_time);
		temp = temp->next;
		if (main_state->philos == temp)
			break ;
	}
	return (true);
}

bool	init_threads(t_main *main_state)
{
	t_philo	*temp;

	temp = main_state->philos;
	pthread_mutex_lock(&main_state->print_log);
	while(1)
	{
		if (pthread_create(&temp->thread, NULL, *routine, temp) != 0)
			return (false);
		temp = temp->next;
		if (temp == main_state->philos)
			break ;
	}
	return (true);
}
