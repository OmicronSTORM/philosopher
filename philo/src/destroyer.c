/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroyer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jowoundi <jowoundi@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 17:23:38 by jowoundi          #+#    #+#             */
/*   Updated: 2025/10/13 18:08:13 by jowoundi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	kill_em_all(t_philo *philo, t_data *data)
{
	int		i;
	t_philo	*temp;

	i = -1;
	pthread_mutex_destroy(&data->mut_dead);
	pthread_mutex_destroy(&data->message);
	while (++i < data->nb_philo)
		pthread_mutex_destroy(&philo->data->fork[i]);
	free(data->fork);
	pthread_mutex_destroy(&philo->lock_meal);
	while (philo)
	{
		temp = philo->next;
		free(philo);
		philo = temp;
	}
	free(data);
}
