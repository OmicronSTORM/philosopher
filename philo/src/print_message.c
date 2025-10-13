/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jowoundi <jowoundi@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 14:43:18 by jowoundi          #+#    #+#             */
/*   Updated: 2025/10/13 18:14:09 by jowoundi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(char *message, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mut_dead);
	if (philo->data->dead)
	{
		pthread_mutex_unlock(&philo->data->mut_dead);
		return ;
	}
	pthread_mutex_unlock(&philo->data->mut_dead);
	pthread_mutex_lock(&philo->data->message);
	printf("%lld philo %d %s\n", ms() - philo->data->s_time, \
		philo->id_philo, message);
	pthread_mutex_unlock(&philo->data->message);
}
