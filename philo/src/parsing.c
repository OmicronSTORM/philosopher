/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jowoundi <jowoundi@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:25:06 by jowoundi          #+#    #+#             */
/*   Updated: 2025/10/03 11:48:07 by jowoundi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parsing(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = -1;
		while (av[i][++j])
		{
			if (ft_isdigit(av[i][j]) != 1)
				return (0);
		}
		if (ft_strlen(av[i]) == 1 && av[i][0] == '0')
			return (0);
		i++;
	}
	return (1);
}
