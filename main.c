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
	both->philo->forks = both->philo->nbr_philo;
	both->philo->thread_id = malloc((both->philo->nbr_philo) * sizeof(pthread_t));
	both->philo->forkstate = malloc(both->philo->nbr_philo * sizeof(pthread_mutex_t));
	both->philo->any_dead = 0;
	//both->philo->indivarray = malloc((both->philo->nbr_philo) * sizeof(t_indiv *));

}

void	mutex_changestate(t_indiv *indiv, char state)
{
	if (state == 'l')
	{
		if(pthread_mutex_lock(&indiv->fork_R) != 0)
			printf("merda\n");
		if(pthread_mutex_lock(&indiv->fork_L) != 0)
			printf("merda\n");
	}
	else if (state == 'u')
	{
		if(pthread_mutex_unlock(&indiv->fork_R) != 0)
			printf("merda\n");
		if(pthread_mutex_unlock(&indiv->fork_L) != 0)
			printf("merda\n");
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

void	philoindv_init(t_both *both, int pos)
{
	both->indivarray[pos]->fork_R = both->philo->forkstate[pos];
	printf("funcmutex %p temp %d\n", &both->philo->forkstate[pos] , pos);
	if (pos != 0)
		both->indivarray[pos]->fork_L = both->philo->forkstate[pos - 1];
}

void	leftfork(t_both *both)
{
	both->indivarray[0]->fork_L = both->philo->forkstate[both->philo->nbr_philo - 2];
}

void	printcorrectindiv(t_indiv *indiv)
{
	int	temp = indiv->nbr_philo;
	printf("nbr philo %d\n", indiv->nbr_philo);
	indiv = indiv->next;
	while (temp != indiv->nbr_philo)
	{
		printf("nbr philo %d\n", indiv->nbr_philo);
		indiv = indiv->next;
	}
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
			printf("temp %d\n", temp);
			pthread_mutex_init(&both.philo->forkstate[temp], NULL);
			printf("mutex %p temp %d\n", &both.philo->forkstate[temp], temp);
			philoindv_init(&both, temp);
		}
		leftfork(&both);
		//printcorrectindiv(both.indiv);
		temp = -1;
		while (++temp < both.philo->nbr_philo - 1)
		{
			pthread_create(&both.philo->thread_id[temp], NULL, &func, both.indivarray[temp]);
		}
		freelst(&both);
		free(both.philo->thread_id);
		free(both.philo->forkstate);
	}
	else
		printf("not enough args\n");
	return (0);
}
//grab fork, eat, leave fork, sleep, think, repeat