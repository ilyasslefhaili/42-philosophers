/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilefhail <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:06:53 by ilefhail          #+#    #+#             */
/*   Updated: 2022/04/13 15:06:54 by ilefhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

void	ft_usleep(long long l)
{
	long long	k;

	k = l + get_time();
	while (k > get_time())
		usleep(10);
}

void	*philo_actv(void *par)
{
	t_philos_data	*st;

	st = par;
	while (1)
	{
		if (st->lt != 0 && st->t->time_to_die < get_time() - st->lt)
			return (NULL);
		pthread_mutex_lock(&st->mt[st->id]);
		ft_print("has taken a fork", st);
		pthread_mutex_lock(&st->mt[(st->id + 1) % st->n_philo]);
		ft_print("has taken a fork", st);
		ft_print("is eating", st);
		pthread_mutex_lock(st->t->print_lock);
		st->n_ofm += 1;
		st->lt = get_time();
		pthread_mutex_unlock(st->t->print_lock);
		ft_usleep(st->t->time_to_eat);
		pthread_mutex_unlock(&st->mt[st->id]);
		pthread_mutex_unlock(&st->mt[(st->id + 1) % st->n_philo]);
		ft_print("is sleeping", st);
		ft_usleep(st->t->time_to_sleep);
		ft_print("is thinking", st);
	}
	return (NULL);
}

long long	get_time(void)
{
	long long			time;
	struct timeval		t;

	gettimeofday(&t, NULL);
	time = t.tv_sec * 1000 + t.tv_usec / 1000;
	return (time);
}

int	check_arg(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j] != '\0')
		{
			if (av[i][j] > '9')
				return (1);
			else if (av[i][j] < '0')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	fill_times(int ac, char **av, t_times *c)
{
	c->print_lock = malloc(sizeof(pthread_mutex_t));
	if (!c->print_lock)
		return (-1);
	pthread_mutex_init(c->print_lock, NULL);
	c->time_to_die = ft_atoi(av[2]);
	c->time_to_eat = ft_atoi(av[3]);
	c->time_to_sleep = ft_atoi(av[4]);
	ac = 0;
	if (av[5])
	{
		c->n_to_philo_eat = ft_atoi(av[5]);
		if (c->n_to_philo_eat == 0)
			return (0);
	}
	return (ft_atoi(av[1]));
}
