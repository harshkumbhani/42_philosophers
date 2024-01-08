/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkumbhan <hkumbhan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 13:46:32 by hkumbhan          #+#    #+#             */
/*   Updated: 2024/01/08 14:44:24 by hkumbhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_everything(t_main *main_state)
{
	t_philo	*next;
	t_philo	*current;

	current = main_state->philos;
	if (current == NULL)
		return ;
	next = current->next;
	pthread_mutex_destroy(&main_state->print_log);
	while (next != main_state->philos)
	{
		pthread_mutex_destroy(&current->m_philo);
		pthread_mutex_destroy(current->right_f);
		free(current->right_f);
		free(current);
		current = next;
		next = current->next;
	}
	pthread_mutex_destroy(&current->m_philo);
	pthread_mutex_destroy(current->right_f);
	free(current->right_f);
	free(current);
	main_state->philos = NULL;
}
