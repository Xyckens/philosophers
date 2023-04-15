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

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo
{
	int				nbr_philo;
	int				ttd;
	int				tte;
	int				tts;
	int				forks;
	int				nbr_eat;
	pthread_t		*thread_id;
	pthread_mutex_t	*forkstate;
	struct timeval	begin;
}				t_philo;

typedef struct s_indiv
{
	int				nbr_philo;
	pthread_mutex_t	fork_R;
	pthread_mutex_t	fork_L;
	struct timeval	time_eaten;
	int				nbr_eaten;
	struct s_indiv	*next;
}				t_indiv;

typedef struct s_both
{
	t_philo	*philo;
	t_indiv	*indiv;
}				t_both;

int		ft_atoi(const char *nptr);
void	printstats(t_indiv *indiv, int len);


t_indiv	*connectthem(t_philo *philo, struct timeval teatn);
void	freelst(t_both *both);

void	sleeping(t_both *both);
int		eating(t_both *both);

#endif
