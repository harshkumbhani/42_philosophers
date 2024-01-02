/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkumbhan <hkumbhan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 10:28:20 by hkumbhan          #+#    #+#             */
/*   Updated: 2024/01/02 11:16:04 by hkumbhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	gettime(void)
{
	struct timeval	time;

	time = (struct timeval){};
	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + (time.tv_usec / 1000));
}

int	ft_usleep(size_t ms)
{
	size_t	start;

	start = gettime();
	while (gettime() - start < ms)
		usleep(100);
	return (0);
}
