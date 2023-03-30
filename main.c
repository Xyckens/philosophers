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

void	philostruct_init(t_philo *philo, char **argv)
{
	philo->nbr_philo = ft_atoi(argv[1]) + 1;
	philo->ttd = ft_atoi(argv[2]);
	philo->tte = ft_atoi(argv[3]);
	philo->tts = ft_atoi(argv[4]);
	philo->forks = philo->nbr_philo;
	philo->thread_id = malloc(philo->nbr_philo * sizeof(pthread_t));
	philo->forkstate = malloc(philo->nbr_philo * sizeof(pthread_mutex_t));
}

void	*func(void *arg)
{
	t_philo	*philo;

	philo = arg;
	//printf("ainda nao vi timestamp, philo nbr %d\n", philo->nbr_philo);
	return (NULL);
}

/*void	detach_this(pthread_t *threads, int temp)
{
		while (temp-- > 0)
		{
			printf("threads %lu\n", philo->threads[temp]);
			pthread_detach(philo->threads[temp]);
			pthread_mutex_destroy(philo->forkstate[temp]);
			usleep(10);
		}
}*/

/*
void foo()
{
    pthread_mutex_lock(&foo_mutex);
   // Do work.
    pthread_mutex_unlock(&foo_mutex);
}
*/

void	philoindv_init(t_philo *philo, t_indiv *indiv, int pos)
{

}

int	main(int argc, char **argv)
{
	t_philo	philo;
	t_indiv	indiv;
	int temp;
	struct timeval begin;

	if (argc >= 5)
	{
		philostruct_init(&philo, argv);
		if (argc >= 6)
			philo.nbr_eat = ft_atoi(argv[5]);
		else
			philo.nbr_eat = -1;
		temp = philo.nbr_philo;
		gettimeofday(&begin, NULL);
		while (philo.nbr_philo-- > 1)
		{
			pthread_create(&philo.thread_id[temp], NULL, &func, &philo);
			pthread_mutex_init(&philo.forkstate[temp], NULL);
			philoindv_init(&philo, &indiv, temp);
			sleeping(&philo, begin, philo.nbr_philo);
			usleep(1);
		}
		//detach_this(&philo, temp);
	}
	else
		printf("not enough args\n");
	return (0);
}
//grab fork, eat, leave fork, sleep, think, repeat