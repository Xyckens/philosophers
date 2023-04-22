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
	(void)flag;
	pthread_mutex_lock(&indiv->philo->deaths);
	if (indiv->is_dead > 0 || indiv->philo->any_dead > 0)
	{
		pthread_mutex_unlock(&indiv->philo->deaths);
		return (1);
	}
	else if (indiv->philo->ttd < mytime(indiv->time_eaten))
	{
		indiv->philo->any_dead++;
		pthread_mutex_unlock(&indiv->philo->deaths);
		indiv->is_dead++;
		printf("%ld ms "
			"%d is  dieded  💀\n", mytime(indiv->philo->begin), indiv->nbr_philo);
		return (1);
	}
	pthread_mutex_unlock(&indiv->philo->deaths);
	return (0);
}

void	*d(void *arg)
{
	t_indiv	*indiv;

	indiv = (t_indiv *)arg;
	while (indiv->nbr_eaten != 0)
	{
		if (death(indiv, 0) == 1)
			break ;
	}
	return (NULL);
}
