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

void	philo_init(t_philo *philo, char **argv)
{
	philo->nbr_philo = ft_atoi(argv[1]);
	philo->ttd = ft_atoi(argv[2]);
	philo->tte = ft_atoi(argv[3]);
	philo->tts = ft_atoi(argv[4]);
	philo->forks = philo->nbr_philo;
	philo->threadID = malloc(philo->nbr_philo * sizeof(pthread_t));
}

void	*func(void *arg)
{
	t_philo	*philo;

	philo = arg;
	printf("ainda nao vi timestamp, philo nbr %d\n", philo->nbr_philo);
	return (NULL);
}

/*void	detach_this(pthread_t *threads, int temp)
{
		while (temp-- > 0)
		{
			printf("threads %lu\n", threads[temp]);
			pthread_detach(threads[temp]);
			usleep(10);
		}
}*/

int	main(int argc, char **argv)
{
	t_philo	philo;
	int temp;

	if (argc >= 5)
	{
		philo_init(&philo, argv);
		if (argc >= 6)
			philo.nbr_eat = ft_atoi(argv[5]);
		else
			philo.nbr_eat = -1;
		temp = philo.nbr_philo;
		while (philo.nbr_philo-- > 0)
		{
			pthread_create(&philo.threadID[temp], NULL, &func, &philo);
			usleep(10);
		}
		//detach_this(philo.threadID, temp);
	}
	else
		printf("not enough args\n");
	return (0);
}
