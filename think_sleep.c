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

void	sleeping(t_both *both)
{
	struct timeval now;

	usleep(both->philo->tts);
	gettimeofday(&now, NULL);
	printf("%ld ms ", (now.tv_usec - both->philo->begin.tv_usec)/100);
	printf("%d is 😴😴😴\n", both->indiv->nbr_philo);

}

int	eating(t_both *both)
{
	struct timeval now;

	gettimeofday(&now, NULL);
	if (both->indiv->time_eaten.tv_sec - now.tv_sec > 1)
	{
		printf("%ld %d is 💀💀💀💀\n", now.tv_usec - both->philo->begin.tv_usec, both->indiv->nbr_philo);
		return (1);
	}
	if (both->philo->ttd > both->indiv->time_eaten.tv_usec - now.tv_usec)
	{
		printf("%ld %d is 💀💀💀💀\n", now.tv_usec - both->philo->begin.tv_usec, both->indiv->nbr_philo);
		return (1);
	}
	both->indiv->time_eaten = now;
	printf("%ld %d is 😫🍝😫🍝\n", now.tv_usec - both->philo->begin.tv_usec, both->indiv->nbr_philo);
	usleep(both->philo->tte);
	return (0);
}