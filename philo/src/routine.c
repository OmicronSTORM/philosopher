/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jowoundi <jowoundi@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 18:28:31 by jowoundi          #+#    #+#             */
/*   Updated: 2025/10/21 16:17:37 by jowoundi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *data)
{
	t_philo			*philo;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;

	philo = (t_philo *)data;
	left_fork = philo->fork_l;
	right_fork = philo->fork_r;
	if (philo->id_philo % 2 != 0)
	{
		left_fork = philo->fork_r;
		right_fork = philo->fork_l;
	}
	program(philo, left_fork, right_fork);
	return (NULL);
}

bool	fat(t_philo *philo)
{
	t_philo	*runner;

	runner = philo;
	if (philo->data->nb_eat == -1)
		return (false);
	while (runner)
	{
		if (!runner->finish)
			return (true);
		runner = runner->next;
	}
	return (false);
}

static void	start_threads(t_philo *philo, pthread_t *pid)
{
	t_philo	*runner;
	int		i;

	runner = philo;
	i = 0;
	philo->data->s_time = ms();
	while (runner)
	{
		pthread_create(&pid[i], NULL, routine, runner);
		runner = runner->next;
		i++;
	}
	usleep(1);
}

static void	monitor(t_philo *philo)
{
	t_philo	*runner;

	runner = philo;
	while (1)
	{
		if (is_dead(runner))
			break ;
		runner = runner->next;
		if (!runner)
		{
			runner = philo;
			pthread_mutex_lock(&philo->lock_meal);
			if (fat(philo))
			{
				pthread_mutex_unlock(&philo->lock_meal);
				break ;
			}
			pthread_mutex_unlock(&philo->lock_meal);
			usleep(1);
		}
	}
}

void	set(t_philo *philo)
{
	pthread_t	*pid;
	int			i;

	pid = malloc(sizeof(pthread_t) * philo->data->nb_philo);
	if (!pid)
		return ;
	start_threads(philo, pid);
	monitor(philo);
	i = -1;
	while (++i < philo->data->nb_philo)
		pthread_join(pid[i], NULL);
	free(pid);
}
