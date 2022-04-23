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

void	print_lock(char *s, t_times *t)
{
	if (sem_wait(t->sem_lock) != 0)
		kill(0, SIGINT);
	printf("%lld philo %d %s\n", get_time(t->first_time), t->index + 1, s);
	if (sem_post(t->sem_lock) != 0)
		kill(0, SIGINT);
}

void	*cheeck_death(void	*par)
{
	t_times		*t;

	t = par;
	while (1)
	{
		if (sem_wait(t->sem_lock) != 0)
				kill(0, SIGINT);
		if (t->n_ofm != 0 && t->time_to_die < get_time(t->first_time) - t->time_last_eat)
		{
			printf("%lld philo %d is die\n", get_time(t->first_time),
				t->index + 1);
			kill(0, SIGINT);
			return (NULL);
		}
		if(t->av[5])
		{
			if (t->n_ofm >= t->n_to_philo_eat)
			{
				if (sem_post(t->sem_lock) != 0)
					kill(0, SIGINT);
				sem_post(t->sem);
				sem_post(t->sem);
				exit(0);
			}
		}
		if (sem_post(t->sem_lock) != 0)
			kill(0, SIGINT);
	}
	return (NULL);
}

void	philo_activ(t_times *t)
{
	pthread_t	check;

	if (pthread_create(&check, NULL, cheeck_death, t) != 0)
		kill(0, SIGINT);
	while (1)
	{
		if (sem_wait(t->sem) != 0)
			kill(0, SIGINT);
		print_lock("has taken a fork", t);
		if (sem_wait(t->sem) != 0)
			kill(0, SIGINT);
		print_lock("has taken a fork", t);
		if (sem_wait(t->sem_lock) != 0)
			kill(0, SIGINT);
		t->time_last_eat = get_time(t->first_time);
		if (sem_post(t->sem_lock) != 0)
			kill(0, SIGINT);
		print_lock("is eating", t);
		t->n_ofm += 1;
		usleep(t->time_to_eat * 1000);
		if (sem_post(t->sem) != 0)
			kill(0, SIGINT);
		if (sem_post(t->sem) != 0)
			kill(0, SIGINT);
		print_lock("is sleeping", t);
		usleep(t->time_to_sleep * 1000);
		print_lock("is thinking", t);
	}
}

int	main(int ac, char **av)
{
	int		nph;
	t_times	*tim;
	int		r_fork;
	int		i;

	if (check_arg(av, ac) == 1)
		return (1);
	tim = malloc(sizeof(t_times));
	if (!tim)
		exit(1);
	tim->first_time = get_time(0);
	tim->av = av;
	nph = fill_times(ac, av, tim);
	if (nph <= 0)
		exit(1);
	sem_unlink("ilyass");
	tim->sem = sem_open("ilyass", O_CREAT, 0777, nph);
	sem_unlink("ana");
	tim->sem_lock = sem_open("ana", O_CREAT, 0777, 1);
	tim->index = 0;
	while (tim->index < nph)
	{
		r_fork = fork();
		if (r_fork == 0)
			philo_activ(tim);
		usleep(100);
		tim->index++;
	}
	i = 0;
	while (i < nph)
	{
		waitpid(-1, NULL, 0);
		i++;
	}
	printf("all philos are taken his mils\n");
}
