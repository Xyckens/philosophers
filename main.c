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
	both->philo->nbr_philo = ft_atoi(argv[1]) + 1;
	both->philo->ttd = ft_atoi(argv[2]);
	both->philo->tte = ft_atoi(argv[3]);
	both->philo->tts = ft_atoi(argv[4]);
	both->philo->forks = both->philo->nbr_philo;
	both->philo->thread_id = malloc((both->philo->nbr_philo) * sizeof(pthread_t));
	both->philo->forkstate = malloc(both->philo->nbr_philo * sizeof(pthread_mutex_t));
}

void	*func(void *arg)
{
	t_both *both;

	both = arg;
	sleeping(both);
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
	//both->indiv->thread_id = both->philo->thread_id[pos];
	both->indiv->fork_L = both->philo->forkstate[pos];
	if (pos != both->philo->nbr_philo - 1)
		both->indiv->fork_R = both->philo->forkstate[pos + 1];

}

t_indiv	*rightfork(t_both *both)
{
	int	temp;
	t_indiv	*lst;

	lst = both->indiv;
	temp = 0;
	while (temp++ < both->philo->nbr_philo - 2)
		both->indiv = both->indiv->next;
	both->indiv->fork_R = both->philo->forkstate[0];
	both->indiv = lst;
	return (both->indiv);
}

int	main(int argc, char **argv)
{
	t_both *both;
	int temp;
	struct timeval begin;

	both = NULL;
	if (argc >= 5)
	{
		philostruct_init(both, argv);
		if (argc >= 6)
			both->philo->nbr_eat = ft_atoi(argv[5]);
		else
			both->philo->nbr_eat = -1;
		temp = both->philo->nbr_philo;
		gettimeofday(&begin, NULL);
		both->philo->begin = begin;
		both->indiv = connectthem(both->philo, begin);
		while (temp-- > 1)
		{
			pthread_mutex_init(&both->philo->forkstate[temp], NULL);
			philoindv_init(both, temp);
		}
		both->indiv = rightfork(both);
		temp = both->philo->nbr_philo;
		while (temp-- > 1)
		{
			printf("temp%d\n",temp);
			pthread_create(&both->philo->thread_id[temp], NULL, &func, both);
			both->indiv = both->indiv->next;
			usleep(1);
		}
		//printstats(indiv, philo.nbr_philo);
		free(both->philo->thread_id);
		free(both->philo->forkstate);
		freelst(&both->indiv, both->philo->nbr_philo);
	}
	else
		printf("not enough args\n");
	return (0);
}
//grab fork, eat, leave fork, sleep, think, repeat