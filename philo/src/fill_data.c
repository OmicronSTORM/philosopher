/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jowoundi <jowoundi@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 19:07:55 by jowoundi          #+#    #+#             */
/*   Updated: 2025/10/23 18:01:05 by jowoundi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	*fill_data(char **line)
{
	t_data			*data;
	pthread_mutex_t	*fork_array;
	int				i;

	i = -1;
	data = NULL;
	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	pthread_mutex_init(&data->mut_dead, NULL);
	pthread_mutex_init(&data->message, NULL);
	data->nb_eat = -1;
	data->dead = false;
	data->nb_philo = ft_atoi(line[1]);
	data->ttd = ft_atoi(line[2]);
	data->tte = ft_atoi(line[3]);
	data->tts = ft_atoi(line[4]);
	if (line[5])
		data->nb_eat = ft_atoi(line[5]);
	fork_array = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!fork_array)
		return (NULL);
	while (++i < data->nb_philo)
		pthread_mutex_init(&fork_array[i], NULL);
	data->fork = fork_array;
	return (data);
}
