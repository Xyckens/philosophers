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

void	sleeping(t_philo *philo, struct timeval begin, int nphil)
{
	struct timeval now;

	usleep(philo->tts);
	gettimeofday(&now, NULL);
	printf("%ld ms %d is 😴😴😴\n", (now.tv_usec - begin.tv_usec)/100, nphil);
}

void	eating(t_philo *philo, struct timeval begin, int nphil)
{
	struct timeval now;

	usleep(philo->tte);
	gettimeofday(&now, NULL);
	printf("%ld %d is 😫🍝😫🍝\n", now.tv_usec - begin.tv_usec, nphil);
}