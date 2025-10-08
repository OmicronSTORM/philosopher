/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jowoundi <jowoundi@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 18:28:31 by jowoundi          #+#    #+#             */
/*   Updated: 2025/10/08 17:06:09 by jowoundi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mut_dead);
	pthread_mutex_lock(&philo->lock_meal);
	if (ms() - philo->last_meal > philo->data->ttd)
	{
		pthread_mutex_unlock(&philo->lock_meal);
		pthread_mutex_lock(&philo->data->message);
		printf("%lld philo %d died\n", ms() - philo->data->s_time, philo->id_philo);
		pthread_mutex_unlock(&philo->data->message);
		return (philo->data->dead = true, pthread_mutex_unlock(&philo->data->mut_dead), true);
	}
	pthread_mutex_unlock(&philo->lock_meal);
	pthread_mutex_unlock(&philo->data->mut_dead);
	return (false);
}

bool	take_fork(pthread_mutex_t *fork, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mut_dead);
	if (philo->data->dead)
		return (pthread_mutex_unlock(&philo->data->mut_dead), false);
	pthread_mutex_unlock(&philo->data->mut_dead);
	pthread_mutex_lock(fork);
	print_message("has taken a fork", philo);
	return (true);
}

bool	eat(t_philo *philo, pthread_mutex_t *lf, pthread_mutex_t *rf)
{
	if (!take_fork(lf, philo))
		return (false);
	if (!take_fork(rf, philo))
		return (false);
	print_message("is eating", philo);
	dodo(philo->data->tte);
	pthread_mutex_unlock(lf);
	pthread_mutex_unlock(rf);
	pthread_mutex_lock(&philo->lock_meal);
	philo->last_meal = ms();
	pthread_mutex_unlock(&philo->lock_meal);
	philo->eat_count += 1;
	return (true);
}


void	program(t_philo *philo, pthread_mutex_t *lf, pthread_mutex_t *rf)
{
	pthread_mutex_lock(&philo->lock_meal);
	philo->last_meal = ms();
	pthread_mutex_unlock(&philo->lock_meal);
	if (philo->id_philo % 2 == 0)
		dodo(philo->data->tte / 2);
	while (philo->data->nb_eat == -1 || philo->eat_count < philo->data->nb_eat)
	{
		if (!eat(philo, lf, rf))
			return ;
		print_message("is sleeping", philo);
		dodo(philo->data->tts);
		print_message("is thinking", philo);
	}
	pthread_mutex_lock(&philo->lock_meal);
	philo->finish = true;
	pthread_mutex_unlock(&philo->lock_meal);
}

void	*routine(void *data)
{
	t_philo	*philo;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;

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

bool fat(t_philo *philo)
{
	t_philo *runner;

	runner = philo;
	while (runner)
	{
		if (!runner->finish)
			return (true);
		runner = runner->next;
	}
	return (false);
}

void	set(t_philo *philo)
{
	pthread_t	*pid;
	t_philo		*runner;
	int			i;

	pid = NULL;
	runner = philo;
	i = 0;
	pid = malloc(sizeof(pthread_t) * philo->data->nb_philo);
	if (!pid)
		return ;
	philo->data->s_time = ms();
	while (runner)
	{
		pthread_create(&pid[i], NULL, routine, runner);
		runner = runner->next;
		i++;
	}
	runner = philo;
	while (1)
	{
		if (is_dead(runner))
			break;
		runner = runner->next;
		if (runner == NULL)
		{
			runner = philo;
			pthread_mutex_lock(&philo->lock_meal);
			if (fat(philo))
			{
				pthread_mutex_unlock(&philo->lock_meal);
				break;
			}
			pthread_mutex_unlock(&philo->lock_meal);

			usleep(1);
		}
	}
	i = 0;
	while (i < philo->data->nb_philo)
	{
		pthread_join(pid[i], NULL);
		i++;
	}
}