/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkumbhan <hkumbhan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:32:54 by hkumbhan          #+#    #+#             */
/*   Updated: 2024/01/04 17:32:32 by hkumbhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdbool.h>
# include <limits.h>

/* --------------------------------- Colours -------------------------------- */

#define NC		"\e[0m"
#define YELLOW	"\e[33m"
#define BYELLOW	"\e[1;33m"
#define RED		"\e[31m"
#define GREEN	"\e[32m"

/* --------------------------------- structs -------------------------------- */

typedef enum s_state
{
	EATING,
	SLEEPING,
	THINKING,
	DIED,
	FORK,
}	t_state;

typedef	struct s_arg
{
	int		nb_philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		eat_number;
}	t_arg;

typedef struct s_philo
{
	bool			die_flag;
	bool			done_eat;
	int				index;
	int				times_eaten;
	size_t			time_last_eat;
	size_t			*start_time;
	pthread_t		thread;
	pthread_mutex_t	*right_f;
	pthread_mutex_t	*left_f;
	pthread_mutex_t	*print_log;
	t_arg			*data;
	struct s_philo	*previous;
	struct s_philo	*next;
}	t_philo;


typedef struct s_main
{
	size_t			start_time;
	pthread_mutex_t	print_log;
	t_philo			*philos;
}	t_main;


/* ------------------------- Time related functions ------------------------- */

size_t	gettime(void);
int		ft_usleep(size_t ms);

/* ----------------------------- Init functions ----------------------------- */

bool	init(t_main *philos, t_arg *args, int ac, char **av);
void	init_arguments(char **av, t_arg *args);
void	lst_add_back(t_main *main_state, t_philo *new_node);
void	*ft_calloc(size_t count, size_t size);
bool	init_mutex(t_main *main_state);
bool	init_threads(t_main *main_state);
void	*routine(void *arg);

/* ---------------------------------- Utils --------------------------------- */

bool	check(char **av);
long	ft_atol(const char *str);

#endif



// starts with left fork
// philo 1 right fork = philo->next->left_fork
// philo 2 right fork = philo->next->left_fork
//
//
