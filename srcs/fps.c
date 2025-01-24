/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:21:15 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/15 17:03:48 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define N_PER_SECOND 1000000000L

/* -------------------------------------------------------------------------- */
/* Function used to retrieve the time difference between two timespec         */
/* -------------------------------------------------------------------------- */
void	subtract_timespec(const t_time *end, const t_time *start, t_time *res)
{
	res->tv_sec = end->tv_sec - start->tv_sec;
	res->tv_nsec = end->tv_nsec - start->tv_nsec;
	if (res->tv_nsec < 0)
	{
		res->tv_sec -= 1;
		res->tv_nsec += N_PER_SECOND;
	}
}

/* -------------------------------------------------------------------------- */
/* Function used to limit the frame rate, if the time it took for the map to  */
/* update was faster than the expected frame's time.                          */
/* -------------------------------------------------------------------------- */
void	limit_frame_rate(const t_time *f_start_time)
{
	t_time	f_end_time;
	t_time	elapsed_time;
	t_time	remaining_time;
	long	target_frame_ns;
	long	elapsed_ns;

	clock_gettime(CLOCK_MONOTONIC, &f_end_time);
	subtract_timespec(&f_end_time, f_start_time, &elapsed_time);
	target_frame_ns = N_PER_SECOND / TARGET_FPS;
	elapsed_ns = elapsed_time.tv_sec * N_PER_SECOND + elapsed_time.tv_nsec;
	if (elapsed_ns < target_frame_ns)
	{
		remaining_time.tv_sec = 0;
		remaining_time.tv_nsec = target_frame_ns - elapsed_ns;
		nanosleep(&remaining_time, NULL);
	}
}

/* -------------------------------------------------------------------------- */
/* Function used to retrieve the number of frames drawn per second.           */
/* -------------------------------------------------------------------------- */
int	calculate_fps(t_data *data)
{
	static t_time	start_time = {0, 0};
	static int		frame_count = 0;
	t_time			current_time;
	t_time			elapsed_time;

	if (start_time.tv_sec == 0)
		clock_gettime(CLOCK_MONOTONIC, &start_time);
	clock_gettime(CLOCK_MONOTONIC, &current_time);
	frame_count++;
	subtract_timespec(&current_time, &start_time, &elapsed_time);
	if (elapsed_time.tv_sec >= 1)
	{
		data->fps = frame_count;
		frame_count = 0;
		clock_gettime(CLOCK_MONOTONIC, &start_time);
	}
	return ((frame_count * N_PER_SECOND) / (elapsed_time.tv_sec * N_PER_SECOND
			+ elapsed_time.tv_nsec));
}
