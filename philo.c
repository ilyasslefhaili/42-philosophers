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

int fill_times(int ac, char **av, times_t *c)
{
	c->print_lock = malloc(sizeof(pthread_mutex_t));
	if (!c->print_lock)
		return (-1);
	pthread_mutex_init(c->print_lock, NULL);
	c->time_to_die = ft_atoi(av[2]);
	c->time_to_eat = ft_atoi(av[3]);
	c->time_to_sleep = ft_atoi(av[4]);
	if (ac == 5)
		c->n_to_philo_eat = 0;
	else
		c->n_to_philo_eat = ft_atoi(av[5]);
	if(c->n_to_philo_eat == 0)
		return (0);
	else if(c->n_to_philo_eat < 0)
		return (-1);
	return(ft_atoi(av[1]));
}

void ft_usleep(int time)
{
	long long  l;

	l = get_time() + time;
	while (l > get_time())
		usleep(100);
}

void ft_print(char *s, philos_data_t *data)
{
	pthread_mutex_lock(data->t->print_lock);
	printf("%lld philo %d %s\n",get_time() ,data->id + 1, s);
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
		if(st->lt != 0 && st->t->time_to_die < st->kt - st->lt)
			return (NULL);
		pthread_mutex_lock(&st->mt[(st->id + 1) % st->n_philo]);
		ft_print("has taken a fork", st);
		st->lt = get_time();
		ft_print("is eating", st);
		st->n_ofm += 1;
		ft_usleep(st->t->time_to_eat);
		pthread_mutex_unlock(&st->mt[st->id]);
		pthread_mutex_unlock(&st->mt[(st->id + 1)% st->n_philo]);
		ft_print("is sleeping", st);
		ft_usleep(st->t->time_to_sleep);
		ft_print("is thinking", st);
	}
	return(NULL);
}

void	*create_thread(pthread_mutex_t *mutex, int nph, times_t *tim)
{
	philos_data_t	*philo_d;
	pthread_t		*philo;
	int				i;

	philo_d = malloc(sizeof(philos_data_t) * nph);
	philo = malloc(sizeof(pthread_t) * nph);
	if (!(philo_d || philo))
		return (NULL);
	i = 0;
	while (i < nph)
	{
		philo_d[i].lt = 0;
		philo_d[i].n_ofm = 0;
		philo_d[i].t = tim;
		philo_d[i].n_philo = nph;
		philo_d[i].id = i;
		philo_d[i].mt = mutex;
		philo_d[i].kt = get_time();
		if(pthread_create(&philo[i], NULL, philo_actv, &philo_d[i]) != 0)
			return (NULL);
		usleep(100);
		i++;
	}
	return (philo_d);
}

int check_mils(philos_data_t *philo_d, times_t *tim, int nph)
{
	int i;
	int k;

	i = 0;
	k = 0;
	while (i < nph)
	{
		if (philo_d[i].n_ofm >= tim->n_to_philo_eat)
			k++;
		i++;
	}
	if (k == nph)
	{
		pthread_mutex_lock(tim->print_lock);
		printf("all philos are taken his mils\n");
		return (0);
	}
	return (1);
}

int	waiting_died(philos_data_t *philo_d, times_t *tim, int nph, char **av)
{
	int i;

	i = 0;
	while (1)
	{
		i = 0;
		while (i < nph)
		{
			if(philo_d[i].lt != 0 && philo_d[i].t->time_to_die < philo_d[i].kt - philo_d[i].lt)
			{
				pthread_mutex_lock(tim->print_lock);
				printf("\x1b[0;31m""%lld philo %d is die\n""\x1b[0m", get_time(), philo_d[i].id + 1);
				return (0);
			}	
			i++;
		}
		if (av[5])
		{
			if (check_mils(philo_d, tim, nph) == 0)
				return (0);
		}
	}
}

int	init_mutex(pthread_mutex_t	*mutex, int nph)
{
	int i;

	i = 0;
	while (i < nph)
	{
		if(pthread_mutex_init(&mutex[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

int main(int ac, char **av)
{
	int   nph;
	times_t			*tim;
	philos_data_t	*philo_d;
	pthread_mutex_t	*mutex;

	philo_d = NULL;
	if (check_arg(av) == 1)
		return (1);	
	tim = malloc(sizeof(times_t));
	if(!tim)
		return (1);
	nph = fill_times(ac, av, tim);
	if (nph <= 0)
		return (nph);
	mutex = malloc(sizeof(pthread_mutex_t) * nph);
	if (!mutex )
		return (1);
	if(init_mutex(mutex, nph) == 1)
		return (0);
	philo_d = create_thread(mutex, nph, tim);
	if(philo_d == NULL)
		return (1);
	waiting_died(philo_d, tim, nph, av);
}
