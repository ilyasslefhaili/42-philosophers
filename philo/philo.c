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

void	*create_thread(pthread_mutex_t *mutex, int nph, t_times *tim)
{
	t_philos_data	*philo_d;
	pthread_t		*philo;
	int				i;

	philo_d = malloc(sizeof(t_philos_data) * nph);
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
		if (pthread_create(&philo[i], NULL, philo_actv, &philo_d[i]) != 0)
			return (NULL);
		usleep (100);
		i++;
	}
	return (philo_d);
}

int	check_mils(t_philos_data *philo_d, t_times *tim, int nph)
{
	int		i;
	int		k;

	i = 0;
	k = 0;
	while (i < nph)
	{
		pthread_mutex_lock(tim->print_lock);
		if (philo_d[i].n_ofm >= tim->n_to_philo_eat)
			k++;
		i++;
		pthread_mutex_unlock(tim->print_lock);
	}
	if (k == nph)
	{
		pthread_mutex_lock(tim->print_lock);
		printf("all philos are taken his mils\n");
		return (0);
	}
	return (1);
}

int	waiting(t_philos_data *philo_d, t_times *tim, int nph, char **av)
{
	int		i;

	while (1)
	{
		i = -1;
		while (i++ < nph)
		{
			pthread_mutex_lock(tim->print_lock);
			if ((philo_d[i].lt != 0
					&& philo_d[i].t->time_to_die
					< get_time(tim->first_time) - philo_d[i].lt)
				|| nph == 1)
			{	
				printf("\x1b[0;31m""%lld philo %d is die\n""\x1b[0m",
					get_time(tim->first_time), philo_d[i].id + 1);
				return (0);
			}
			pthread_mutex_unlock(tim->print_lock);
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
	int		i;

	i = 0;
	while (i < nph)
	{
		if (pthread_mutex_init(&mutex[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	int				nph;
	t_times			*tim;
	t_philos_data	*philo_d;
	pthread_mutex_t	*mutex;

	philo_d = NULL;
	if (check_arg(av) == 1)
		return (1);
	tim = malloc(sizeof(t_times));
	if (!tim)
		return (1);
	nph = fill_times(ac, av, tim);
	if (nph <= 0)
		return (nph);
	mutex = malloc(sizeof(pthread_mutex_t) * nph);
	if (!mutex)
		return (1);
	if (init_mutex(mutex, nph) == 1)
		return (1);
	philo_d = create_thread(mutex, nph, tim);
	if (philo_d == NULL)
		return (1);
	waiting(philo_d, tim, nph, av);
}
