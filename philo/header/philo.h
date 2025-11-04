/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jowoundi <jowoundi@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:42:38 by jowoundi          #+#    #+#             */
/*   Updated: 2025/11/04 15:41:48 by jowoundi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <time.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>

typedef struct s_data
{
	int				nb_philo;
	int				ttd;
	int				tte;
	int				tts;
	int				nb_eat;
	bool			dead;
	pthread_mutex_t	*fork;
	long long		s_time;
	pthread_mutex_t	mut_dead;
	pthread_mutex_t	message;
}	t_data;

typedef struct s_philo
{
	int						id_philo;
	int						eat_count;
	bool					finish;
	pthread_mutex_t			*fork_l;
	pthread_mutex_t			*fork_r;
	pthread_mutex_t			lock_meal;
	long long				last_meal;
	t_data					*data;
	struct s_philo			*next;
}	t_philo;

int			ft_atoi(const char *str);
t_data		*fill_data(char **line);
int			parsing(char **av);
int			ft_isdigit(int c);
t_philo		*init_philo(t_data *data);
void		set(t_philo *philo);
int			ft_strlen(char *str);
long long	ms(void);
void		dodo(int ms);
void		print_message(char *message, t_philo *philo);
void		kill_em_all(t_philo *philo, t_data *data);
bool		is_dead(t_philo *philo);
bool		take_fork(pthread_mutex_t *fork, t_philo *philo);
bool		eat(t_philo *philo, pthread_mutex_t *lf, pthread_mutex_t *rf);
void		program(t_philo *philo, pthread_mutex_t *lf, pthread_mutex_t *rf);

#endif