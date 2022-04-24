/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilefhail <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 22:26:59 by ilefhail          #+#    #+#             */
/*   Updated: 2022/04/11 22:27:02 by ilefhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo_bonus.h"

void	sem_eat(sem_t	*sem_a, t_times *t)
{
	if (sem_wait(sem_a) != 0)
		kill(0, SIGINT);
	t->n_ofm += 1;
	t->time_last_eat = get_time(t->first_time);
	if (sem_post(sem_a) != 0)
		kill(0, SIGINT);
}

static void	done(const char *str, int i, unsigned long long *nmbr)
{
	*nmbr = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		*nmbr = *nmbr * 10 + (str[i] - '0');
		i++;
	}
}

void	ft_usleep(int l, long long f)
{
	long long	k;

	k = get_time(f) + l;
	while (k > get_time(f))
		usleep(100);
}

int	ft_atoi(const char *str)
{
	int					i;
	unsigned long long	nmbr;
	int					s;

	i = 0;
	s = 1;
	while (str[i] == '\n' || str[i] == '\v' || str[i] == '\t' || str[i] == ' '
		|| str[i] == '\r' || str[i] == '\f')
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		s *= -1;
		i++;
	}
	done(str, i, &nmbr);
	if (nmbr >= 2147483647 && s == 1)
		return (-1);
	else if (s == -1)
		return (-1);
	return (s * nmbr);
}
