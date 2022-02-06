/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 19:25:31 by acousini          #+#    #+#             */
/*   Updated: 2022/02/02 19:14:41 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

unsigned long long int	time_from_beginning(unsigned long long int start)
{
	return (time_now_in_ms() - start);
}

struct timeval	time_now(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (now);
}

unsigned long long int	time_now_in_ms(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((long long int)(long long int)now.tv_sec * 1000
		+ (long long int)now.tv_usec / 1000);
}

unsigned long long int	time_of_arg_in_ms(struct timeval time)
{
	return ((long long int)(long long int)time.tv_sec * 1000
		+ (long long int)time.tv_usec / 1000);
}

void	wait_in_ms(unsigned long long int ms)
{
	unsigned long long int	until;

	until = time_of_arg_in_ms(time_now()) + ms;
	while (time_of_arg_in_ms(time_now()) < until)
	{
		usleep(1000);
	}
}
