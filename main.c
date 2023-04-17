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
	both->philo->indivarray = malloc((both->philo->nbr_philo) * sizeof(t_indiv *));

}

void	mutex_changestate(t_both *both, char state)
{
	if (state == 'l')
	{
		if(pthread_mutex_lock(&both->indiv->fork_R) != 0)
			printf("merda\n");
		if(pthread_mutex_lock(&both->indiv->fork_L) != 0)
			printf("merda\n");
		printf("fork lock by %d\n", both->indiv->nbr_philo);
	}
	else if (state == 'u')
	{
		if(pthread_mutex_unlock(&both->indiv->fork_R) != 0)
			printf("merda\n");
		if(pthread_mutex_unlock(&both->indiv->fork_L) != 0)
			printf("merda\n");
		printf("fork unlock by %d\n", both->indiv->nbr_philo);
	}
}

void	*func(void *arg)
{
	t_both *both;
	int	temp;

	both = (t_both *)arg;
	temp = both->number;
	printf("temp %d\n", temp);
	//both->indiv = both->indiv->next;
	//while (both->philo->indivarray[temp - 1]->is_dead == 0 && both->philo->indivarray[temp - 1]->nbr_eaten != 0)
	//{
	//	if (any_death(both) == 1 || both->philo->indivarray[temp - 1]->is_dead == 1)
		//	break ;

		printf("a fork lock by %d\n", both->philo->indivarray[temp - 1]->nbr_philo);
		//mutex_changestate(both, 'l');
		//eating(both);
		printf("a fork unlock by %d\n", both->philo->indivarray[temp - 1]->nbr_philo);
		//mutex_changestate(both, 'u');
		//if (any_death(both) == 1 || both->philo->indivarray[temp - 1]->is_dead == 1)
		//	break ;
		//sleeping(both);
	//}
	return (NULL);
}

void	philoindv_init(t_both *both, int pos)
{
	both->indiv->fork_R = both->philo->forkstate[pos];
	if (pos != 1)
		both->indiv->fork_L = both->philo->forkstate[pos - 1];
}

void	leftfork(t_both *both)
{
	int	temp;

	temp = 0;
	while (both->indiv->nbr_philo != 1)
		both->indiv = both->indiv->next;
	both->indiv->fork_L = both->philo->forkstate[both->philo->nbr_philo - 2];
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
		both.indiv = connectthem(both.philo, begin);
		temp = -1;
		while (++temp < both.philo->nbr_philo - 1)
		{
			pthread_mutex_init(&both.philo->forkstate[temp], NULL);
			philoindv_init(&both, temp + 1);
			both.indiv = both.indiv->next;
		}
		leftfork(&both);
		//printcorrectindiv(both.indiv);
		temp = -1;
		while (++temp < both.philo->nbr_philo - 1)
		{
			both.nbr = temp + 1;
			printf("ola %d\n", temp + 1);
			pthread_create(&both.philo->thread_id[temp], NULL, &func, &both);
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