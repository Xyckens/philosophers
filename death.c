/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 18:37:02 by fvieira           #+#    #+#             */
/*   Updated: 2023/04/15 18:37:03 by fvieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	any_death(t_indiv **indivarray)
{
	int	temp;

	temp = 0;
	//printf("philo %d\n", );
	while (indivarray[temp]->nbr_philo != indivarray[0]->philo->nbr_philo - 4)
	{
		printf("temp %d\n", temp);
		printf("max %d\n", indivarray[temp]->philo->nbr_philo - 1);
		printf("is dead %d\n", indivarray[temp]->is_dead);
		if (indivarray[temp]->is_dead == 1)
		{
			printf("ola\n");
			return(1);
		}
		temp++;
	}
	return(0);
}
