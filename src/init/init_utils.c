/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkumbhan <hkumbhan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:00:37 by hkumbhan          #+#    #+#             */
/*   Updated: 2024/01/06 13:38:54 by hkumbhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_bzero(void *s, size_t n)
{
	char	*ptr;
	size_t	i;

	ptr = s;
	i = 0;
	while (i < n)
	{
		ptr[i] = '\0';
		i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (count && (size * count) / count != size)
		return (NULL);
	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}

void	lst_add_back(t_main *main_state, t_philo *new_node)
{
	t_philo	*temp;

	
	if (main_state->philos == NULL)
	{
		new_node->next = new_node;
		new_node->previous = new_node;
		main_state->philos = new_node;
	}
	else
	{
		temp = main_state->philos->previous;
		temp->next = new_node;
		new_node->previous = temp;
		new_node->next = main_state->philos;
		main_state->philos->previous = new_node;
	}
}