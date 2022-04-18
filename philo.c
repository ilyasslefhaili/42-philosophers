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
	c->print_lock = malloc(sizeof(pthread_mutex_t));
	if (!c->print_lock)
		return (0);
	pthread_mutex_init(c->print_lock, NULL);
	c->time_to_die = ft_atoi(av[2]);
	c->time_to_eat = ft_atoi(av[3]);
	c->time_to_sleep = ft_atoi(av[4]);
	if(av[5])
		c->n_to_philo_eat = ft_atoi(av[5]);
	return(ft_atoi(av[1]));
}

void ft_usleep(int time)
{
	long long  l;

	l = get_time() + time;
	while (l > get_time())
	{
		usleep(100);
	}
}

void ft_print(char *s, philos_data_t *data)
{
	pthread_mutex_lock(data->t->print_lock);
	printf("%d %s\n", data->id, s);
	pthread_mutex_unlock(data->t->print_lock);
}
void  *philo_actv(void *par)
{
	philos_data_t *st;

	st = par;
	while (1)
	{	
		pthread_mutex_lock(&st->mt[st->id]);
		ft_print("has taken a fork", st);
		st->kt = get_time();
		////
		if(st->lt != 0 && st->t->time_to_die < st->kt - st->lt)
			return (NULL);
		////
		pthread_mutex_lock(&st->mt[(st->id + 1) % st->n_philo]);
		ft_print("has taken a fork", st);
		st->lt = get_time();
		ft_print("is eating", st);
		ft_usleep(st->t->time_to_eat);
		pthread_mutex_unlock(&st->mt[st->id]);
		ft_print("put down fork", st);
		pthread_mutex_unlock(&st->mt[(st->id + 1)% st->n_philo]);
		ft_print("put down fork", st);
		ft_print("is sleeping", st);
		ft_usleep(st->t->time_to_sleep);
		ft_print("is thinking", st);
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

	ac = 0;
	if (check_arg(av) == 1)
		return (1);
	nph = fill_times(av, &tim);
	philo_d = malloc(sizeof(philos_data_t) * nph);
	mutex = malloc(sizeof(pthread_mutex_t) * nph);
	philo = malloc(sizeof(pthread_t) * nph);
	if (!(philo_d || mutex || philo))
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
		philo_d[i].n_ofm = 0;
		philo_d[i].t = &tim;
		philo_d[i].n_philo = nph;
		philo_d[i].id = i;
		philo_d[i].mt = mutex;
		philo_d[i].kt = get_time();
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
				pthread_mutex_lock(tim.print_lock);
				printf("\x1b[0;31m""%lld philo %d is die\n""\x1b[0m", get_time(), philo_d[i].id + 1);
				return (0);
			}	
			i++;
		}
		// if (av[5])
		// {
		// 	i = 0;
		// 	k = 0;
		// 	while (i < nph)
		// 	{
		// 		if (philo_d[i].n_ofm >= tim.n_to_philo_eat)
		// 			k++;
		// 		i++;
		// 	}
		// 	if (k == nph)
		// 	{
		// 		pthread_mutex_lock(tim.print_lock);
		// 		printf("kalo kamlen\n");
		// 		return (0);
		// 	}
		// }
	}
}
