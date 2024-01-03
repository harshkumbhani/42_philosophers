/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkumbhan <hkumbhan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:37:05 by hkumbhan          #+#    #+#             */
/*   Updated: 2024/01/03 11:37:51 by hkumbhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

# define TIMES_TO_COUNT 21000
# define NC			"\e[0m"
# define YELLOW		"\e[1;33m"
# define BYELLOW	"\e[1;33m"
# define RED		"\e[31m"
# define GREEN		"\e[32m"

typedef struct s_count
{
	pthread_mutex_t	count_mutex;
	unsigned int	count;
}	t_count;

void	*routine(void	*data)
{
	pthread_t		tid;
	t_count			*count;
	unsigned int	i;

	tid = pthread_self();
	count = (t_count *)data;
	pthread_mutex_lock(&count->count_mutex);
	printf("%sThread [%ld]: Count at thread start = %u.%s\n",
		YELLOW, tid, *count, NC);
	pthread_mutex_unlock(&count->count_mutex);
	i = 0;
	while (i < TIMES_TO_COUNT)
	{
		pthread_mutex_lock(&count->count_mutex);
		count->count++;
		i++;
	}
	printf("%sThread [%ld]: Final count = %u.%s\n",
		BYELLOW, tid, *count, NC);
	return (NULL);
}

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	pthread_t	tid1;
	pthread_t	tid2;
	t_count		count;

	count.count = 0;
	pthread_mutex_init(&count.count_mutex, NULL);
// Since each thread counts TIMES_TO_COUNT times and that
	// we have 2 threads, we expect the final count to be
	// 2 * TIMES_TO_COUNT:
	printf("Main: Expected count is %s%u%s\n", GREEN, 
					2 * TIMES_TO_COUNT, NC);
	// Thread creation:
	pthread_create(&tid1, NULL, routine, &count);
	printf("Main: Created first thread [%ld]\n", tid1);
	pthread_create(&tid2, NULL, routine, &count);
	printf("Main: Created second thread [%ld]\n", tid2);
	// Thread joining:
	pthread_join(tid1, NULL);
	printf("Main: Joined first thread [%ld]\n", tid1);
	pthread_join(tid2, NULL);
	printf("Main: Joined second thread [%ld]\n", tid2);
	// Final count evaluation:
	if (count != (2 * TIMES_TO_COUNT))
		printf("%sMain: ERROR ! Total count is %u%s\n", RED, count, NC);
	else
		printf("%sMain: OK. Total count is %u%s\n", GREEN, count, NC);
	return (0);
}

// 1. Assign all values
// 2. Create mutexes
// 3. Lock the shared mutex
// 4. Create threads (threads will be stuck due to shared mutex)
// 5. After creating -> main thread will unlock shared
// 6. Loop through linked list and check if they should die
