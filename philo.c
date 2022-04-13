/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilefhail <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 00:37:44 by ilefhail          #+#    #+#             */
/*   Updated: 2022/04/10 00:37:47 by ilefhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

void fill_times(char **av, times_t *c)
{
	c->n_philo = ft_atoi(av[1]);
	c->time_to_die = ft_atoi(av[2]);
	c->time_to_eat = ft_atoi(av[3]);
	c->time_to_sleep = ft_atoi(av[4]);
	if(av[5])
		c->n_to_philo_eat = ft_atoi(av[5]);
}

void  *philo_actv(void *par)
{
    int i = 0;
	philos_data_t *st;

	st = par;
	pthread_mutex_lock(&st->mt);
    while(i < 1000)
        i++;
	pthread_mutex_unlock(&st->mt);
	//printf("%d\n", i);
    return(NULL);
}

int main(int ac, char **av)
{
	philos_data_t	philo_d;
	pthread_t		*philo;
	int				i;

	ac = 0;
	i = 0;
	if (check_arg(av) == 1)
		return (1);
	fill_times(av, &philo_d.t);
	philo = malloc(sizeof(pthread_t) * philo_d.t.n_philo);
	if(!philo)
		return (1);
	philo_d.f = ft_calloc(4, philo_d.t.n_philo);
	if (!philo_d.f)
		retutn (1);
	while (i < philo_d.t.n_philo)
	{
		printf("%d\n", philo_d.f[i]);
		i++;
	} 
	pthread_mutex_init(&philo_d.mt, NULL);
	while (i < philo_d.t.n_philo)
	{
		pthread_create(&philo[i], NULL, philo_actv, &philo_d);
		i++;
	}
	i = 0;
	while (i < philo_d.t.n_philo)
	{
		pthread_join(philo[i], NULL);
		i++;
	}
}
