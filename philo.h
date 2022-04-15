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

typedef struct philo
{
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int n_to_philo_eat;
	int n_philo;
}times_t;

typedef struct  data_t
{
	times_t *t;
	pthread_mutex_t *mt;
	int	id;
}philos_data_t;

int		ft_atoi(const char *str);
int		check_arg(char **av);
void	*ft_calloc(int count, int size);

#endif

