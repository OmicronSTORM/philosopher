/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jowoundi <jowoundi@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 17:41:31 by jowoundi          #+#    #+#             */
/*   Updated: 2025/11/03 09:12:48 by jowoundi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*n_node(t_data *data, int i)
{
	t_philo	*new_node;

	new_node = malloc(sizeof(t_philo));
	if (!new_node)
		return (NULL);
	new_node->fork_l = &data->fork[i];
	pthread_mutex_init(&new_node->lock_meal, NULL);
	if (i + 1 == data->nb_philo)
		new_node->fork_r = &data->fork[0];
	else
		new_node->fork_r = &data->fork[i + 1];
	new_node->data = data;
	new_node->finish = false;
	new_node->eat_count = 0;
	new_node->id_philo = i + 1;
	new_node->last_meal = 0;
	new_node->next = NULL;
	return (new_node);
}

void	create_node(t_philo **philo, t_data *data, int i)
{
	t_philo	*new_node;
	t_philo	*temp;

	new_node = n_node(data, i);
	if (!new_node)
		return ;
	if (!*philo)
	{
		*philo = new_node;
		return ;
	}
	temp = *philo;
	while (temp->next)
		temp = temp->next;
	temp->next = new_node;
}

void	create_philo(t_philo **philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		create_node(philo, data, i);
		i++;
	}
}

t_philo	*init_philo(t_data *data)
{
	t_philo	*philo;

	philo = NULL;
	create_philo(&philo, data);
	return (philo);
}
