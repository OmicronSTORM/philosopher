/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jowoundi <jowoundi@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 18:21:26 by jowoundi          #+#    #+#             */
/*   Updated: 2025/11/04 15:47:55 by jowoundi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_dead(t_philo *philo)
{
	long long	last_meal;
	bool		should_die;

	pthread_mutex_lock(&philo->lock_meal);
	last_meal = philo->last_meal;
	pthread_mutex_unlock(&philo->lock_meal);
	should_die = ((int)(ms() - last_meal) > philo->data->ttd);
	if (!should_die)
		return (false);
	pthread_mutex_lock(&philo->data->mut_dead);
	if (!philo->data->dead)
		philo->data->dead = true;
	pthread_mutex_unlock(&philo->data->mut_dead);
	pthread_mutex_lock(&philo->data->message);
	printf("%lld philo %d died\n", ms() - philo->data->s_time, \
		philo->id_philo);
	pthread_mutex_unlock(&philo->data->message);
	return (true);
}

bool	take_fork(pthread_mutex_t *fork, t_philo *philo)
{
	bool dead;

	pthread_mutex_lock(&philo->data->mut_dead);
	dead = philo->data->dead;
	pthread_mutex_unlock(&philo->data->mut_dead);
	if (dead)
		return (false);
	pthread_mutex_lock(fork);
	print_message("has taken a fork", philo);
	return (true);
}

bool	eat(t_philo *philo, pthread_mutex_t *lf, pthread_mutex_t *rf)
{
	if (!take_fork(lf, philo))
		return (false);
	if (philo->data->nb_philo == 1)
		return (pthread_mutex_unlock(lf), false);
	if (!take_fork(rf, philo))
		return (pthread_mutex_unlock(lf), false);
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
	if (philo->id_philo % 2 == 1)
		dodo(philo->data->tte / 2);
	while (philo->data->nb_eat == -1 || philo->eat_count < philo->data->nb_eat)
	{
		if (!eat(philo, lf, rf))
			return ;
		print_message("is sleeping", philo);
		dodo(philo->data->tts);
		print_message("is thinking", philo);
		if (philo->data->nb_philo % 2 == 1)
			dodo(philo->data->tte / 2);
	}
	pthread_mutex_lock(&philo->lock_meal);
	philo->finish = true;
	pthread_mutex_unlock(&philo->lock_meal);
}
