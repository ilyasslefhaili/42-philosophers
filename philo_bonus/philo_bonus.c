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

void	*cheeck_death(void	*par)
{
	t_times		*t;

	t = par;
	while (1)
	{
		if (sem_wait(t->sema) != 0)
			kill(0, SIGINT);
		if (t->n_ofm != 0
			&& t->time_to_die < get_time(t->first_time) - t->time_last_eat)
		{
			if (sem_wait(t->sem_lock) != 0)
				kill(0, SIGINT);
			printf("%lld philo %d is die\n", get_time(t->first_time),
				t->index + 1);
			kill(0, SIGINT);
		}
		if (t->av[5])
		{
			if (t->n_ofm == t->n_to_philo_eat)
				ft_exit(t);
		}
		if (sem_post(t->sema) != 0)
			kill(0, SIGINT);
	}
	return (NULL);
}

void	philo_activ(t_times *t, sem_t *sem_a)
{
	pthread_t	check;

	t->sema = sem_a;
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
		sem_eat(sem_a, t);
		print_lock("is eating", t);
		ft_usleep(t->time_to_eat, t->first_time);
		if (sem_post(t->sem) != 0)
			kill(0, SIGINT);
		if (sem_post(t->sem) != 0)
			kill(0, SIGINT);
		print_lock("is sleeping", t);
		ft_usleep(t->time_to_sleep, t->first_time);
		print_lock("is thinking", t);
	}
}

void	wait_proc(int nph)
{
	int	i;

	i = 0;
	while (i < nph)
	{
		waitpid(-1, NULL, 0);
		i++;
	}
}

void	finish(t_times *tim, int nph, sem_t *sem_a)
{
	int		r_fork;
	pid_t	*pid;

	pid = malloc(sizeof(pid) * nph);
	while (tim->index < nph)
	{	
		r_fork = fork();
		if (r_fork < 0)
		{
			while (tim->index > 0)
			{
				kill(pid[tim->index], SIGINT);
				tim->index--;
			}
			exit (1);
		}
		if (r_fork == 0)
			philo_activ(tim, sem_a);
		usleep(100);
		tim->index++;
	}
	wait_proc(nph);
	printf("all philos are taken his mils\n");
}

int	main(int ac, char **av)
{
	int		nph;
	t_times	*tim;
	sem_t	*sem_a;

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
	sem_unlink("philo");
	tim->sem = sem_open("philo", O_CREAT, 0777, nph);
	sem_unlink("print");
	tim->sem_lock = sem_open("print", O_CREAT, 0777, 1);
	sem_unlink("k");
	sem_a = sem_open("k", O_CREAT, 0777, 1);
	tim->index = 0;
	finish(tim, nph, sem_a);
}
