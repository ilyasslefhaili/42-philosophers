/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilefhail <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:06:53 by ilefhail          #+#    #+#             */
/*   Updated: 2022/04/13 15:06:54 by ilefhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

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

void	*ft_calloc(int count, int size)
{
	void				*k;
	int					i;

	i = 0;
	k = malloc(count * size);
	if (!k)
		return (NULL);
	memset(k, 0, size * count);
	return (k);
}