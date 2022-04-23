/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilefhail <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 12:50:26 by ilefhail          #+#    #+#             */
/*   Updated: 2022/04/21 12:50:28 by ilefhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>

typedef struct philo
{
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					n_to_philo_eat;
	int					index;
	sem_t				*sem;
	sem_t				*sem_lock;
	sem_t				*sem_a;
	long long			first_time;
	long long			time_last_eat;
	int					n_ofm;
	char **av;
}t_times;

int			check_arg(char **av, int ac);
int			fill_times(int ac, char **av, t_times *c);
int			ft_atoi(const char *str);
long long	get_time(long long first_time);

#endif
