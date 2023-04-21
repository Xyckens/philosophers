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

int	death(t_indiv *indiv, int flag)
{
	if (flag == 1)
	{
		eating(indiv);
		mutex_changestate(indiv, 'u');
	}
	pthread_mutex_lock(&indiv->philo->deaths);
	if (indiv->is_dead > 0 || indiv->philo->any_dead > 0)
	{
		pthread_mutex_unlock(&indiv->philo->deaths);
		return (1);
	}
	else if (indiv->philo->ttd < mytime(indiv->time_eaten))
	{
		printf("%ld ms "
			"%d is  dieded  💀\n", mytime(indiv->philo->begin) , indiv->nbr_philo);
		indiv->is_dead++;
		indiv->philo->any_dead++;
		pthread_mutex_unlock(&indiv->philo->deaths);
		return (1);
	}
	pthread_mutex_unlock(&indiv->philo->deaths);
	return (0);
}
