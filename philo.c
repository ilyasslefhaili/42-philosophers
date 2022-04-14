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
	philos_data_t *st; 
	st = par;
	while (1)
	{
		pthread_mutex_lock(&st->mt[st->id]); // hez fork
		printf("philo %d has taken a fork %d \n", st->id + 1, st->id);
		pthread_mutex_lock(&st->mt[(st->id + 1) % st->t.n_philo]);
		printf("philo %d has taken a fork %d \n", st->id + 1,( st->id + 1) % st->t.n_philo);
		printf("philo %d is eating\n", st->id + 1);
		usleep(st->t.time_to_eat * 1000);
		pthread_mutex_unlock(&st->mt[st->id]); // 7et fork
		pthread_mutex_unlock(&st->mt[(st->id + 1)% st->t.n_philo]);
		usleep(st->t.time_to_sleep * 1000);
		printf("philo %d is sleeping\n", st->id + 1);
		printf("philod %d is thinking\n", st->id + 1);
	}
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
	philo_d.mt = malloc(sizeof(pthread_mutex_t) * philo_d.t.n_philo);
	if (!philo_d.mt)
		return (1);
	philo = malloc(sizeof(pthread_t) * philo_d.t.n_philo);
	if(!philo)
		return (1);
	philo_d.f = ft_calloc(4, philo_d.t.n_philo);
	if (!philo_d.f)
		return (1);
	
	while (i < philo_d.t.n_philo)
	{
		if(pthread_mutex_init(&philo_d.mt[i], NULL) != 0)
			return (1);
		i++;
	}
	i= 0;
	while (i < philo_d.t.n_philo)
	{
		philo_d.f = i;
		if(pthread_create(&philo[i], NULL, philo_actv, &philo_d) != 0)
			return (1);
		usleep(100);
		i++;
	}
	i = 0;
	while (i < philo_d.t.n_philo)
	{
		if(pthread_join(philo[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}
