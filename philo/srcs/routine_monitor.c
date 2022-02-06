/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_monitor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 12:14:54 by acousini          #+#    #+#             */
/*   Updated: 2022/02/04 21:09:39 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	*monitor(void *data)
{
	t_philo	*philo;
	int		dead;
	int		running;

	dead = 1;
	running = 1;
	philo = (t_philo *)data;
	while (dead && running)
	{
		dead = is_dead(philo);
		running = is_running(philo);
		if (has_eaten(philo) == 0)
			break ;
		usleep(100);
		if (philo->base->nb_eats != -1)
			if (has_eaten_enough(philo))
				break ;
		usleep(100);
	}
	return (NULL);
}

void	*only_one_phil(t_philo *philo, pthread_t dead_check)
{
	int		alive;
	int		running;

	running = 1;
	alive = 1;
	mutex_screen(philo, "has taken a fork\n");
	while (alive && running)
	{
		alive = is_dead(philo);
		running = is_running(philo);
		wait_in_ms(1);
	}
	write_dead(philo);
	pthread_join(dead_check, NULL);
	return (NULL);
}

int	routine_bis(t_philo *philo, pthread_t dead_check)
{
	philo_start_eat(philo);
	philo_start_sleep(philo);
	philo_start_thinking(philo);
	pthread_mutex_lock(&philo->meal_check);
	if (philo->meals_count == philo->base->nb_eats)
	{
		pthread_mutex_unlock(&philo->meal_check);
		pthread_join(dead_check, NULL);
		return (1);
	}
	pthread_mutex_unlock(&philo->meal_check);
	return (0);
}

void	*routine(void *data)
{
	t_philo		*philo;
	pthread_t	dead_check;
	int			alive;
	int			running;

	alive = 1;
	running = 1;
	philo = (t_philo *)data;
	if ((philo->id + 1) % 2 == 1)
		wait_in_ms(philo->base->tte / 2);
	if (pthread_create(&dead_check, NULL, monitor, (void *)philo))
		return (NULL);
	if (philo->base->nb_phils == 1)
		return (only_one_phil(philo, dead_check));
	while (alive && running)
	{
		alive = is_dead(philo);
		running = is_running(philo);
		if (routine_bis(philo, dead_check))
			return (NULL);
		alive = is_dead(philo);
		running = is_running(philo);
	}
	pthread_join(dead_check, NULL);
	return (NULL);
}
