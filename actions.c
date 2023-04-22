/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 22:17:26 by fvieira           #+#    #+#             */
/*   Updated: 2023/04/22 22:17:31 by fvieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	mytime(struct timeval begin)
{
	struct timeval	now;
	long			begintotal;

	gettimeofday(&now, NULL);
	begintotal = (begin.tv_sec * 1000) + (begin.tv_usec / 1000);
	return ((now.tv_sec * 1000) + (now.tv_usec / 1000) - begintotal);
}

void	sleeping(t_indiv *indiv)
{
	pthread_mutex_lock(&indiv->philo->deaths);
	if (indiv->philo->any_dead == 0)
	{
		printf("%ld ms "
			"%d is sleeping 😴\n", mytime(indiv->philo->begin), indiv->nbr_philo);
		pthread_mutex_unlock(&indiv->philo->deaths);
		usleep(indiv->philo->tts * 1000);
	}
	else
		pthread_mutex_unlock(&indiv->philo->deaths);
}

void	thinking(t_indiv *indiv)
{
	pthread_mutex_lock(&indiv->philo->deaths);
	if (indiv->philo->any_dead == 0)
	{
		printf("%ld ms "
			"%d is thinking 🤔\n", mytime(indiv->philo->begin), indiv->nbr_philo);
		pthread_mutex_unlock(&indiv->philo->deaths);
	}
	else
		pthread_mutex_unlock(&indiv->philo->deaths);
}

void	eating(t_indiv *indiv)
{
	struct timeval	now;

	indiv->nbr_eaten--;
	printf("%ld ms "
		"%d is  eating  🍝\n", mytime(indiv->philo->begin), indiv->nbr_philo);
	gettimeofday(&now, NULL);
	indiv->time_eaten = now;
	usleep(indiv->philo->tte * 1000);
}

void	pickingfork(t_indiv *indiv)
{
	pthread_mutex_lock(&indiv->philo->deaths);
	if (indiv->philo->any_dead == 0)
	{
		printf("%ld ms "
			"%d has taken a 🍴\n", mytime(indiv->philo->begin), indiv->nbr_philo);
		pthread_mutex_unlock(&indiv->philo->deaths);
	}
	else
		pthread_mutex_unlock(&indiv->philo->deaths);
}
