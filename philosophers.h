/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:43:11 by fvieira           #+#    #+#             */
/*   Updated: 2023/03/29 14:43:12 by fvieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS
# define PHILOSOPHERS

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

typedef	struct	s_philo
{
	int			nbr_philo;
	int			ttd;
	int			tte;
	int			tts;
	int			forks;
	int			nbr_eat;
	pthread_t	*threadID;
}				t_philo;

int	ft_atoi(const char *nptr);

#endif
