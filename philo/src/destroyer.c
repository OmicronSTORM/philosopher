/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroyer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jowoundi <jowoundi@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 17:23:38 by jowoundi          #+#    #+#             */
/*   Updated: 2025/10/23 17:55:58 by jowoundi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	kill_em_all(t_philo *philo, t_data *data)
{
	int		i;
	t_philo	*temp;
	t_philo	*curr;

	i = -1;
	curr = philo;
	while (curr)
	{
		temp = curr->next;
		pthread_mutex_destroy(&curr->lock_meal);
		free(curr);
		curr = temp;
	}
	while (++i < data->nb_philo)
		pthread_mutex_destroy(&data->fork[i]);
	free(data->fork);
	pthread_mutex_destroy(&data->mut_dead);
	pthread_mutex_destroy(&data->message);
	free(data);
}
