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

long long get_time(void)
{
	long long time;
	struct timeval t;

	gettimeofday(&t, NULL);
	time = t.tv_sec * 1000 + t.tv_usec / 1000;
	return (time); 
}

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
		pthread_mutex_lock(&st->mt[st->id]);
		printf("%lld philo %d has taken a fork %d \n",get_time(), st->id + 1, st->id);
		pthread_mutex_lock(&st->mt[(st->id + 1) % st->t->n_philo]);
		printf("%lld philo %d has taken a fork %d \n",get_time(), st->id + 1,( st->id + 1) % st->t->n_philo);
		printf("\x1b[32m""%lld philo %d is eating\n""\x1b[0m",get_time(), st->id + 1);
		usleep(st->t->time_to_eat * 1000);
		pthread_mutex_unlock(&st->mt[st->id]);
		pthread_mutex_unlock(&st->mt[(st->id + 1)% st->t->n_philo]);
		printf("%lld philo %d is sleeping\n",get_time(), st->id + 1);
		usleep(st->t->time_to_sleep * 1000);
		printf("%lld philod %d is thinking\n", get_time(), st->id + 1);
	}
	return(NULL);
}

int main(int ac, char **av)
{
	philos_data_t	*philo_d;
	pthread_t		*philo;
	times_t			tim;
	int				i;
	pthread_mutex_t	*mutex;

	ac = 0;
	if (check_arg(av) == 1)
		return (1);
	fill_times(av, &tim);
	philo_d = malloc(sizeof(philos_data_t) * tim.n_philo);
	if(!philo_d)
		return (1);
	mutex = malloc(sizeof(pthread_mutex_t) * tim.n_philo);
	if (!mutex)
		return (1);
	philo = malloc(sizeof(pthread_t) * tim.n_philo);
	if (!philo)
		return (1);
	i = 0;
	while (i < tim.n_philo)
	{
		if(pthread_mutex_init(&mutex[i], NULL) != 0)
			return (1);
		i++;
	}
	i = 0;
	while (i < tim.n_philo)
	{
		philo_d[i].t = &tim;
		philo_d[i].id = i;
		philo_d[i].mt = mutex;
		if(pthread_create(&philo[i], NULL, philo_actv, &philo_d[i]) != 0)
			return (1);
		usleep(100);
		i++;
	}
	i = 0;
	while (i < tim.n_philo)
	{
		if(pthread_join(philo[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}
