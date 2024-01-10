/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harsh <harsh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:32:54 by hkumbhan          #+#    #+#             */
/*   Updated: 2024/01/10 13:56:09 by harsh            ###   ########.fr       */
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

# define NC			"\e[0m"
# define BLACK		"\e[0;30m"
# define RED		"\e[0;31m"
# define GREEN		"\e[0;32m"
# define YELLOW		"\e[0;33m"
# define BLUE		"\e[0;34m"
# define PURPLE		"\e[0;35m"
# define CYAN		"\e[0;36m"
# define WHITE		"\e[0;37m"

# define PICK_FORK	1
# define DROP_FORK	2

/* --------------------------------- structs -------------------------------- */

typedef enum s_state
{
	FORK = 0,
	EATING = 1,
	SLEEPING = 2,
	THINKING = 3,
	DIED = 4
}	t_state;

typedef struct s_arg
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
	pthread_mutex_t	m_philo;
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

typedef void	(*t_print_stat)(size_t time, int index, char *str);

/* ------------------------- Time related functions ------------------------- */

size_t	gettime(void);
int		ft_usleep(size_t ms);

/* ----------------------------- Init functions ----------------------------- */

bool	init(t_main *philos, t_arg *args, int ac, char **av);
void	init_arguments(char **av, t_arg *args);
bool	init_mutex(t_main *main_state);
bool	init_threads(t_main *main_state);
bool	check(char **av);

/* -------------------------- Monitors and routines ------------------------- */

void	*routine(void *arg);
void	monitor(t_main *main_state);
void	print_log(t_state state, t_philo *philo);
void	handle_1_nb_of_philos(t_philo *philo);
void	free_everything(t_main *main_state);

/* ---------------------------------- Utils --------------------------------- */

void	lst_add_back(t_main *main_state, t_philo *new_node);
void	*ft_calloc(size_t count, size_t size);
long	ft_atol(const char *str);
void	print_args(t_arg *args);

#endif
