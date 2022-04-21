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

// void	*philo_actv(void *par)
// {

// 	st = par;
// 	while (1)
// 	{
// 		if (st->lt != 0 && st->t->time_to_die < get_time() - st->lt)
// 			return (NULL);
// 		pthread_mutex_lock(&st->mt[st->id]);
// 		ft_print("has taken a fork", st);
// 		pthread_mutex_lock(&st->mt[(st->id + 1) % st->n_philo]);
// 		ft_print("has taken a fork", st);
// 		ft_print("is eating", st);
// 		pthread_mutex_lock(st->t->print_lock);
// 		st->n_ofm += 1;
// 		st->lt = get_time();
// 		pthread_mutex_unlock(st->t->print_lock);
// 		ft_usleep(st->t->time_to_eat);
// 		pthread_mutex_unlock(&st->mt[st->id]);
// 		pthread_mutex_unlock(&st->mt[(st->id + 1) % st->n_philo]);
// 		ft_print("is sleeping", st);
// 		ft_usleep(st->t->time_to_sleep);
// 		ft_print("is thinking", st);
// 	}
// 	return (NULL);
// }
//void	print_lock()

void	print(t_times *t)
{
	sem_wait(t->sem);
	printf("%d has taken fork\n", t->index + 1);
	sem_wait(t->sem);
	printf(" %d has taken fork\n", t->index + 1);
	printf("%d is eating\n", t->index + 1);
	usleep(t->time_to_eat * 1000);
	sem_post(t->sem);
	sem_post(t->sem);
	exit(0);
}

int main(int ac, char **av)
{
	int		nph;
	t_times	*tim;
	int		r_fork;

	if (check_arg(av) == 1)
		return (1);
	tim = malloc(sizeof(t_times));
	if (!tim)
		exit(1);
	nph = fill_times(ac, av, tim);
	if(nph <= 0)
		exit(1);
	sem_unlink("ilyas");
	sem_unlink("ana");
	tim->sem = sem_open("ilyas", O_CREAT, 0777, nph);
	tim->sem_lock = sem_open("ana", O_CREAT, 0777, 1);
	tim->index = 0;
	while (tim->index < nph)
	{
		r_fork = fork();
		if (r_fork == 0)
			print(tim);
		tim->index++;
	}
	waitpid(-1, NULL, 0);
}