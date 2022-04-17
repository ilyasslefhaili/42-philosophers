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

int fill_times(char **av, times_t *c)
{
	c->time_to_die = ft_atoi(av[2]);
	c->time_to_eat = ft_atoi(av[3]);
	c->time_to_sleep = ft_atoi(av[4]);
	if(av[5])
		c->n_to_philo_eat = ft_atoi(av[5]);
	return(ft_atoi(av[1]));
}

void  *philo_actv(void *par)
{
	philos_data_t *st;

	st = par;
	while (1)
	{
		pthread_mutex_lock(&st->mt[st->id]);
		st->kt = get_time();
		if(st->lt != 0 && st->t->time_to_die < st->kt - st->lt)
			return (NULL);
		printf("%lld philo %d take a fork\n", get_time(), st->id + 1);
		pthread_mutex_lock(&st->mt[(st->id + 1) % st->n_philo]);
		printf("%lld philo %d take a fork\n", get_time(), st->id + 1);
		printf("\x1b[32m""%lld philo %d is eating\n""\x1b[0m",get_time(), st->id + 1);
		st->lt = get_time();
		usleep(st->t->time_to_eat * 1000);
		pthread_mutex_unlock(&st->mt[st->id]);
		pthread_mutex_unlock(&st->mt[(st->id + 1)% st->n_philo]);
		printf("%lld philo %d is sleeping\n",get_time(), st->id + 1);
		usleep(st->t->time_to_sleep * 1000);
		printf("%lld philo %d is thinking\n", get_time(), st->id + 1);
	}
	return(NULL);
}

int main(int ac, char **av)
{
	philos_data_t	*philo_d;
	int   nph;
	pthread_t		*philo;
	times_t			tim;
	int				i;
	pthread_mutex_t	*mutex;
	int k;

	k = 0;
	ac = 0;
	if (check_arg(av) == 1)
		return (1);
	nph = fill_times(av, &tim);
	philo_d = malloc(sizeof(philos_data_t) * nph);
	if(!philo_d)
		return (1);
	mutex = malloc(sizeof(pthread_mutex_t) * nph);
	if (!mutex)
		return (1);
	philo = malloc(sizeof(pthread_t) * nph);
	if (!philo)
		return (1);
	i = 0;
	while (i < nph)
	{
		if(pthread_mutex_init(&mutex[i], NULL) != 0)
			return (1);
		i++;
	}
	i = 0;
	while (i < nph)
	{
		philo_d[i].lt = 0;
		philo_d[i].t = &tim;
		philo_d[i].n_philo = nph;
		philo_d[i].id = i;
		philo_d[i].mt = mutex;
		//philo_d[i].l = &k;
		if(pthread_create(&philo[i], NULL, philo_actv, &philo_d[i]) != 0)
			return (1);
		usleep(100);
		i++;
	}
	while (1)
	{
		i = 0;
		while (i < nph)
		{
			if(philo_d[i].lt != 0 && philo_d[i].t->time_to_die < philo_d[i].kt - philo_d[i].lt)
			{
				//pthread_mutex_lock(&m);
				usleep((tim.time_to_eat + tim.time_to_die) * 1000);
				printf("\x1b[0;31m""%lld philo %d is die\n""\x1b[0m", get_time(), philo_d[i].id + 1);
				return (0);
			}	
			i++;
		}
	}
}
