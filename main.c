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
}

void	mutex_changestate(t_both *both, char state)
{
	if (state == 'l')
	{
		pthread_mutex_lock(&both->indiv->fork_R);
		pthread_mutex_lock(&both->indiv->fork_L);
	}
	else if (state == 'u')
	{
		pthread_mutex_unlock(&both->indiv->fork_R);
		pthread_mutex_unlock(&both->indiv->fork_L);
	}
}

void	*func(void *arg)
{
	t_both *both;
	int		death_flag;

	both = (t_both *)arg;
	death_flag = 0;
	printf("numero do philo %d\n", both->indiv->nbr_philo);
	while (death_flag == 0 && both->indiv->nbr_eaten != 0)
	{
		mutex_changestate(both, 'l');
		death_flag = eating(both);
		mutex_changestate(both, 'u');
		sleeping(both);
		printf("death %d\n", death_flag);
	}
	printf("ola\n");
	//printf("ainda nao vi timestamp, philo nbr %d\n", philo->nbr_philo);
	return (NULL);
}

/*
void foo()
{
    pthread_mutex_lock(&foo_mutex);
   // Do work.
    pthread_mutex_unlock(&foo_mutex);
}
*/

void	philoindv_init(t_both *both, int pos)
{
	int	temp;

	temp = pos;
	while (temp-- > 1 && both->indiv != NULL)
		both->indiv = both->indiv->next;
	both->indiv->fork_L = both->philo->forkstate[pos];
	if (pos != both->philo->nbr_philo - 1)
		both->indiv->fork_R = both->philo->forkstate[pos + 1];

}

t_indiv	*rightfork(t_both *both)
{
	int	temp;

	temp = 0;
	while (temp++ < both->philo->nbr_philo - 2)
		both->indiv = both->indiv->next;
	both->indiv->fork_R = both->philo->forkstate[0];
	while (both->indiv->nbr_philo != 1)
		both->indiv = both->indiv->next;
	return (both->indiv);
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
		temp = both.philo->nbr_philo;
		gettimeofday(&begin, NULL);
		both.philo->begin = begin;
		both.indiv = connectthem(both.philo, begin);
		while (temp-- > 1)
		{
			pthread_mutex_init(&both.philo->forkstate[temp], NULL);
			philoindv_init(&both, temp);
		}
		both.indiv = rightfork(&both);
		temp = 0;
		while (++temp < both.philo->nbr_philo)
		{
			pthread_create(&both.philo->thread_id[temp], NULL, &func, &both);
			printf("nbr %d \n",both.indiv->nbr_philo);
			both.indiv = both.indiv->next;
			usleep(300);
		}

		//printstats(indiv, philo.nbr_philo);
		freelst(&both);
		free(both.philo->thread_id);
		free(both.philo->forkstate);
	}
	else
		printf("not enough args\n");
	return (0);
}
//grab fork, eat, leave fork, sleep, think, repeat