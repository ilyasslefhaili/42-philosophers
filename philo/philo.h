/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilefhail <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 22:27:42 by ilefhail          #+#    #+#             */
/*   Updated: 2022/04/11 22:27:43 by ilefhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <signal.h>

typedef struct philo
{
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					n_to_philo_eat;
	pthread_mutex_t		*print_lock;
}t_times;

typedef struct data_t
{
	t_times			*t;
	pthread_mutex_t	*mt;
	int				id;
	long long		lt;
	long long		kt;
	int				n_philo;
	int				n_ofm;
	int				back;
	pthread_mutex_t	*mutex_lock;
}t_philos_data;

long long	get_time(void);
int			ft_atoi(const char *str);
int			check_arg( char **av);
int			fill_times(int ac, char **av, t_times *c);
void		ft_print(char *s, t_philos_data *data);
void		*philo_actv(void *par);

#endif
