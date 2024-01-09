/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_and_mutexes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkumbhan <hkumbhan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 17:15:58 by hkumbhan          #+#    #+#             */
/*   Updated: 2024/01/09 09:00:25 by hkumbhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_left_forks(t_main *main_state)
{
	t_philo	*temp;

	temp = main_state->philos;
	while (true)
	{
		temp->left_f = temp->next->right_f;
		temp = temp->next;
		if (temp == main_state->philos)
			break ;
	}
}

bool	init_mutex(t_main *main_state)
{
	t_philo	*temp;

	temp = main_state->philos;
	if (pthread_mutex_init(&main_state->print_log, NULL) != 0)
		return (false);
	while (true)
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
	init_left_forks(main_state);
	return (true);
}

bool	init_threads(t_main *main_state)
{
	t_philo	*temp;

	temp = main_state->philos;
	pthread_mutex_lock(&main_state->print_log);
	while (true)
	{
		if (pthread_create(&temp->thread, NULL, *routine, temp) != 0)
			return (false);
		temp = temp->next;
		if (temp == main_state->philos)
			break ;
	}
	return (true);
}
