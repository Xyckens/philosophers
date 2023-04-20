/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvieira <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:43:24 by fvieira           #+#    #+#             */
/*   Updated: 2023/03/29 14:43:25 by fvieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philostruct_init(t_both *both, char **argv)
{
	both->philo =  malloc(sizeof(t_philo));
	both->philo->nbr_philo = ft_atoi(argv[1]) + 1;
	both->philo->ttd = ft_atoi(argv[2]);
	both->philo->tte = ft_atoi(argv[3]);
	both->philo->tts = ft_atoi(argv[4]);
	both->philo->thread_id = malloc((both->philo->nbr_philo) * sizeof(pthread_t));
	both->philo->any_dead = 0;
}

void	mutex_changestate(t_indiv *indiv, char state)
{
	if (state == 'l')
	{
		pthread_mutex_lock(indiv->fork_r);
		pthread_mutex_lock(indiv->fork_l);
		pickingfork(indiv);
	}
	else if (state == 'u')
	{
		pthread_mutex_unlock(indiv->fork_r);
		pthread_mutex_unlock(indiv->fork_l);
	}
}

void	*func(void *arg)
{
	t_indiv	*indiv;

	indiv = (t_indiv *)arg;
	while (indiv->is_dead == 0 && indiv->nbr_eaten != 0)
	{
		if (indiv->is_dead == 1 || indiv->philo->any_dead == 1)
			break ;
		mutex_changestate(indiv, 'l');
		eating(indiv);
		mutex_changestate(indiv, 'u');
		if (indiv->is_dead == 1 || indiv->philo->any_dead == 1)
			break ;
		sleeping(indiv);
		thinking(indiv);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_both both;
	int temp;
	struct timeval begin;

	if (argc >= 5)
	{
		philostruct_init(&both, argv);
		if (argc >= 6)
			both.philo->nbr_eat = ft_atoi(argv[5]);
		else
			both.philo->nbr_eat = -1;
		gettimeofday(&begin, NULL);
		both.philo->begin = begin;
		both.indivarray = connectthem(&both, begin);
		temp = -1;
		while (++temp < both.philo->nbr_philo - 1)
		{
			pthread_mutex_init(&both.philo->forkstate[temp], NULL);
			both.indivarray[temp]->fork_r = &both.philo->forkstate[temp];
			if (temp < both.philo->nbr_philo - 1)
				both.indivarray[temp + 1]->fork_l = &both.philo->forkstate[temp];
			if (temp + 1 == both.philo->nbr_philo - 1)
			{
				both.indivarray[0]->fork_l = &both.philo->forkstate[temp];
				both.indivarray[temp]->fork_r = &both.philo->forkstate[temp];
			}
		}
		temp = -1;
		while (++temp < both.philo->nbr_philo)
		{
			pthread_mutex_init(&both.philo->forkstate[temp], NULL);
			both.indivarray[temp]->fork_r = &both.philo->forkstate[temp];
			if (temp < both.philo->nbr_philo - 1)
				both.indivarray[temp + 1]->fork_l = &both.philo->forkstate[temp];
			if (temp + 1 == both.philo->nbr_philo - 1)
				both.indivarray[0]->fork_l = &both.philo->forkstate[temp];
		}
		temp = -1;
		while (++temp < both.philo->nbr_philo - 1)
		{
			pthread_create(&both.philo->thread_id[temp], NULL, &func, both.indivarray[temp]);
		}
		freelst(&both);
		free(both.philo->thread_id);
	}
	else
		printf("not enough args\n");
	return (0);
}
//grab fork, eat, leave fork, sleep, think, repeat

/*		
		temp = -1;
		while (++temp < both.philo->nbr_philo - 1)
		{
			pthread_mutex_init(&both.philo->forkstate[temp], NULL);
			both.indivarray[temp]->fork_r = &both.philo->forkstate[temp];
			if (temp < both.philo->nbr_philo - 1)
				both.indivarray[temp + 1]->fork_l = &both.philo->forkstate[temp];
			if (temp + 1 == both.philo->nbr_philo - 1)
			{
				both.indivarray[0]->fork_l = &both.philo->forkstate[temp];
				both.indivarray[temp]->fork_r = &both.philo->forkstate[temp];

			}
		}
		*/