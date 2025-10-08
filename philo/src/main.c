/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jowoundi <jowoundi@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:12:41 by jowoundi          #+#    #+#             */
/*   Updated: 2025/10/03 15:12:08 by jowoundi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	*data;
	t_philo	*philo;

	if (ac == 5 || ac == 6)
	{
		if (parsing(av) == 0)
			return (printf("incorrect values\n"), 0);
		data = NULL;
		philo = NULL;
		data = fill_data(av);
		philo = init_philo(data);
		set(philo);
	}
	else
		printf("(n_of_philo) (t_to_die) (t_to_eat) (t_to_sleep) [n_of_eat]\n");
	return (0);
}
