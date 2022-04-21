/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilefhail <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 11:22:30 by ilefhail          #+#    #+#             */
/*   Updated: 2022/04/21 11:22:34 by ilefhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo_bonus.h"

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

int main(int ac, char **av)
{
	int		nph;
	t_times	*tim;

	if (check_arg(av) == 1)
		return (1);
	tim = malloc(sizeof(t_times));
	nph = fill_times(ac, av, tim);
}