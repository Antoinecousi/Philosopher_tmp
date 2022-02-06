/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 15:13:43 by acousini          #+#    #+#             */
/*   Updated: 2022/02/04 21:13:39 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	clean_each_philosopher(t_philo *philo)
{
	pthread_mutex_destroy(philo->left_fork);
	free(philo->left_fork);
}

void	clean_base(t_base *base, char *str)
{
	int		i;

	i = 0;
	if (base)
	{
		if (base->malloced == 1)
		{
			while (&base->philosophers[i] && i < base->nb_phils)
			{
				clean_each_philosopher(&base->philosophers[i]);
				i++;
			}
			if (base->malloced == 1)
				free(base->philosophers);
		}
		pthread_mutex_destroy(&base->screen_lock);
		pthread_mutex_destroy(&base->die_lock);
		pthread_mutex_destroy(&base->running_check);
		free(base);
	}
	ft_putstr(str);
}

int	main(int argc, char **argv)
{
	t_base	*base;

	if (!(argc >= 5 && argc <= 6))
		return (write(1, "Usage is ./philo phil_nbr tts tte tts totalmeal"
				, 48));
	base = malloc(sizeof(t_base));
	if (!base)
		return (write(1, "Couldn't malloc struct in main. Exit\n", 38));
	fill_base(base, argv + 1, argc);
	return (0);
}
