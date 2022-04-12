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

void fill_times(char **av, times_t *c)
{
	c->n_philo = ft_atoi(av[1]);
	c->time_to_die = ft_atoi(av[2]);
	c->time_to_eat = ft_atoi(av[3]);
	c->time_to_sleep = ft_atoi(av[4]);
	if(av[5])
		c->n_to_philo_eat = ft_atoi(av[5]);
}

int check_arg(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j] != '\0')
		{
			if(av[i][j] > '9')
				return (1);
			else if(av[i][j] < '0')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

void  *print(void *par)
{
    int i = 0;

    while(i <1000)
    {
        i++;
        *(int*)par = *(int*)par + 1;
    }
    printf("%d\n", *(int*)par);
    return(NULL);
}

int main(int ac, char **av)
{
	times_t c;

	if (check_arg(av) == 1)
		return (1);
	fill_times(av, &c);
	printf("%d\n", c.n_philo);
	printf("%d\n", c.time_to_die);
}
