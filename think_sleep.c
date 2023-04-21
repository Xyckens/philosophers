/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think_sleep.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:42:38 by fvieira           #+#    #+#             */
/*   Updated: 2023/03/30 16:42:39 by fvieira          ###   ########.fr       */
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
		pthread_mutex_unlock(&indiv->philo->deaths);
		printf("%ld ms "
			"%d is sleeping 😴\n", mytime(indiv->philo->begin), indiv->nbr_philo);
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
		pthread_mutex_unlock(&indiv->philo->deaths);
		printf("%ld ms "
			"%d is thinking 🤔\n", mytime(indiv->philo->begin), indiv->nbr_philo);
	}
	else
		pthread_mutex_unlock(&indiv->philo->deaths);
}

void	eating(t_indiv *indiv)
{
	struct timeval	now;

	indiv->nbr_eaten--;
	gettimeofday(&now, NULL);
	indiv->time_eaten = now;
	pthread_mutex_lock(&indiv->philo->deaths);
	if (indiv->philo->any_dead == 0)
	{
		pthread_mutex_unlock(&indiv->philo->deaths);
		printf("%ld ms "
			"%d is  eating  🍝\n", mytime(indiv->philo->begin), indiv->nbr_philo);
		usleep(indiv->philo->tte * 1000);
	}
	else
		pthread_mutex_unlock(&indiv->philo->deaths);
}

void	pickingfork(t_indiv *indiv)
{
	pthread_mutex_lock(&indiv->philo->deaths);
	if (indiv->philo->any_dead == 0)
	{
		printf("%ld ms "
			"%d has taken a 🍴\n", mytime(indiv->philo->begin), indiv->nbr_philo);
	}
	pthread_mutex_unlock(&indiv->philo->deaths);
}
