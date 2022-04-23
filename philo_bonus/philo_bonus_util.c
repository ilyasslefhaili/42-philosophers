/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilefhail <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 12:52:18 by ilefhail          #+#    #+#             */
/*   Updated: 2022/04/21 12:52:20 by ilefhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo_bonus.h"

int	check_arg(char **av, int ac)
{
	int	i;
	int	j;

	if(ac < 5 || ac > 6)
		return (1);
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
	c->first_time = get_time(0);
	c->time_to_die = ft_atoi(av[2]);
	if (c->time_to_die < 0)
		return (0);
	c->time_to_eat = ft_atoi(av[3]);
	if (c->time_to_die < 0)
		return (0);
	c->time_to_sleep = ft_atoi(av[4]);
	if (c->time_to_die < 0)
		return (0);
	ac = 0;
	if (av[5])
	{
		c->n_to_philo_eat = ft_atoi(av[5]);
		if (c->n_to_philo_eat == 0)
			return (0);
	}
	c->n_ofm = 0;
	return (ft_atoi(av[1]));;
}

long long	get_time(long long first_time)
{
	long long			time;
	struct timeval		t;

	gettimeofday(&t, NULL);
	time = t.tv_sec * 1000 + t.tv_usec / 1000 - first_time;
	return (time);
}
