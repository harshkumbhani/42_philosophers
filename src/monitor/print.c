/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harsh <harsh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 16:23:30 by hkumbhan          #+#    #+#             */
/*   Updated: 2024/05/05 14:05:27 by harsh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_random_color_state(size_t time, int index, char *str)
{
	int			i;
	const char	*colors[7] = {
		BLACK, GREEN, BLUE, YELLOW, PURPLE, CYAN, WHITE
	};

	i = index % 7;
	printf("%s%lu %d %s"NC"\n", colors[i], time, index, str);
}

void	print_died(size_t time, int index, char *str)
{
	printf(RED"%lu %d %s"NC"\n", time, index, str);
}

void	print_log(t_state state, t_philo *philo)
{
	static t_print_stat	printoperations[] = {
		print_random_color_state, print_random_color_state,
		print_random_color_state,
		print_random_color_state, print_died
	};
	static char			*str[] = {
		"has taken a fork", "is eating", "is sleeping",
		"is thinking", "died"
	};

	pthread_mutex_lock(philo->print_log);
	if (philo->die_flag == false)
	{
		printoperations[state](gettime() - *(philo->start_time),
			philo->index, str[state]);
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
