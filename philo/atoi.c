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
#include "philo.h"

void	ft_print(char *s, t_philos_data *data)
{
	pthread_mutex_lock(data->t->print_lock);
	printf("%lld philo %d %s\n", get_time(data->t->first_time), data->id + 1, s);
	pthread_mutex_unlock(data->t->print_lock);
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
	if (nmbr >= 2147483647)
		return (-1);
	return (s * nmbr);
}
