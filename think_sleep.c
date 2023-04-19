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
	int	time_diff;

	gettimeofday(&now, NULL);
	time_diff = (begin.tv_sec * 1000) + (begin.tv_usec / 1000);
	return ((now.tv_sec * 1000) + (now.tv_usec / 1000) - time_diff);
}

/*void	msleep(int time)
{
	usleep(time * 1000);
}*/

void	sleeping(t_indiv *indiv)
{
	printf("%ld ms %d is 😴😴😴😴\n", mytime(indiv->philo->begin),indiv->nbr_philo);
	usleep(indiv->philo->tts * 1000);
}

void	thinking(t_indiv *indiv)
{
	printf("%ld ms %d is 🤔🤔🤔🤔\n", mytime(indiv->philo->begin),indiv->nbr_philo);
	usleep(60 * 1000);
}

void	eating(t_indiv *indiv)
{
	struct timeval now;

	gettimeofday(&now, NULL);
	// if (both->indiv->time_eaten.tv_sec - now.tv_sec > 1)
	// {
	// 	printf("%ld %d is 💀💀💀💀\n", time(both->philo->begin), both->indiv->nbr_philo);
	// 	both->indiv->is_dead = 1;
	// }
	if (indiv->philo->ttd < indiv->time_eaten.tv_usec - now.tv_usec)
	{
		printf("%ld ms %d is 💀💀💀💀\n", mytime(indiv->philo->begin), indiv->nbr_philo);
		indiv->is_dead = 1;
		indiv->philo->any_dead = 1;
	}
	else
	{
		indiv->nbr_eaten--;
		printf("%ld ms %d is 😫🍝😫🍝\n", mytime(indiv->philo->begin), indiv->nbr_philo);
		usleep(indiv->philo->tte * 1000);
		indiv->time_eaten = now;
	}
}

/*
	if (indiv->philo->ttd < mytime(now))
	{
		printf("%ld ms %d is 💀💀💀💀\n", mytime(indiv->philo->begin), indiv->nbr_philo);
		indiv->is_dead = 1;
		indiv->philo->any_dead = 1;
	}
	*/