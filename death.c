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

int	death(t_indiv *indiv)
{
	if (indiv->philo->ttd < mytime(indiv->time_eaten))
	{
		printf("%ld ms %d is  dieded  💀\n", mytime(indiv->philo->begin), indiv->nbr_philo);
		indiv->is_dead = 1;
		indiv->philo->any_dead = 1;
		return (1);
	}
	return (0);
}
