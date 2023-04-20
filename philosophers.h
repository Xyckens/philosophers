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
	int				nbr_eat;
	int				any_dead;
	pthread_t		*thread_id;
	pthread_mutex_t	forkstate[250];
	struct timeval	begin;
}				t_philo;

typedef struct s_indiv
{
	int				nbr_philo;
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	*fork_l;
	t_philo			*philo;
	struct timeval	time_eaten;
	int				nbr_eaten;
	int				is_dead;
	struct s_indiv	*next;
}				t_indiv;

typedef struct s_both
{
	t_indiv	**indivarray;
	t_philo	*philo;
}				t_both;

int		ft_atoi(const char *nptr);
void	printstats(t_indiv *indiv, int len);

t_indiv	**connectthem(t_both *begin, struct timeval teatn);
void	freelst(t_both *both);

void	sleeping(t_indiv *indiv);
void	eating(t_indiv *indiv);
void	thinking(t_indiv *indiv);
void	pickingfork(t_indiv *indiv);

void	mutex_changestate(t_indiv *indiv, char state);

int		any_death(t_indiv **indiv);
#endif
