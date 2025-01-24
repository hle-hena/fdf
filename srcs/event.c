/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:26:38 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/15 16:59:53 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* -------------------------------------------------------------------------- */
/* Function used to handle the event of rotation. The rot_n value are the     */
/* rotation using the key input, and the rp_n value are the rotation using    */
/* the mouse input.                                                           */
/* -------------------------------------------------------------------------- */
void	rotate_event(t_data *data)
{
	if (data->event.rot_y && !data->proj)
		do_rot(&data->wld.cam.rot, &data->wld.base, data->event.rot_y, 2);
	if (data->event.rot_x && !data->proj)
		do_rot(&data->wld.cam.rot, &data->wld.base, data->event.rot_x, 1);
	if (data->event.rot_z && !data->proj)
		do_rot(&data->wld.cam.rot, &data->wld.base, data->event.rot_z, 3);
	if (data->event.rp_y && data->proj)
		do_rot(&data->wld.cam.rot, &data->wld.base, data->event.rp_y, 2);
	if (data->event.rp_x && data->proj)
		do_rot(&data->wld.cam.rot, &data->wld.base, data->event.rp_x, 1);
}

/* -------------------------------------------------------------------------- */
/* Function used to handle the event of movement.                             */
/* -------------------------------------------------------------------------- */
void	move_event(t_data *data)
{
	if (data->event.mo_u)
		go_up(data, data->event.mo_u);
	if (data->event.mo_f)
		move_forward(data, data->event.mo_f);
	if (data->event.mo_s)
		move_side(data, data->event.mo_s);
}

/* -------------------------------------------------------------------------- */
/* Function used to handle the event of scaling.                              */
/* -------------------------------------------------------------------------- */
void	scale_event(t_data *data)
{
	if (data->event.sc)
		data->wld.cam.scale += data->event.sc;
	if (data->wld.cam.scale < 1)
		data->wld.cam.scale = 1;
	if (data->event.sc)
		data->event.sc = 0;
}

/* -------------------------------------------------------------------------- */
/* Function used to handle the event of incrementing the value specified in   */
/* the control window.                                                        */
/* -------------------------------------------------------------------------- */
void	inc_event(t_data *data)
{
	if (data->event.inc)
	{
		if (data->modif.ind == 0)
			data->modif.fog += data->event.inc * 0.1;
		else if (data->modif.ind == 1)
			data->modif.mo_speed += data->event.inc * 0.1;
		else if (data->modif.ind == 2)
			data->modif.rot_speed += data->event.inc;
		else if (data->modif.ind == 3)
			data->modif.fov = (int)(data->modif.fov + data->event.inc) % 360;
		else if (data->modif.ind == 4)
		{
			data->modif.f_plane += data->event.inc
				* (15 + (data->modif.f_plane / 15));
			if (data->modif.f_plane <= 0)
				data->modif.f_plane = 1;
		}
		else if (data->modif.ind == 5)
		{
			data->modif.height += data->event.inc * 0.1;
			if (data->modif.height <= 0.1)
				data->modif.height = 0.1;
		}
	}
}

/* -------------------------------------------------------------------------- */
/* Function used to create a game loop.                                       */
/* It first deletes the whole map, then handle all of the input events before */
/* redrawing the map, and finaly update the terminal status and calculate the */
/* framerate, and limits it if necessary.                                     */
/* -------------------------------------------------------------------------- */
int	event_loop(t_data *data)
{
	static int	update = 0;
	int			temp;
	int			fps;
	t_time		frame_start_time;

	clock_gettime(CLOCK_MONOTONIC, &frame_start_time);
	ft_bzero((void *)mlx_get_data_addr(data->img, &temp, &temp, &temp),
		data->win_len * data->win_wid * sizeof(int));
	inc_event(data);
	rotate_event(data);
	move_event(data);
	scale_event(data);
	draw_map(data, 1);
	fps = calculate_fps(data);
	if (fps != 0)
		data->d_time = TARGET_FPS / fps;
	limit_frame_rate(&frame_start_time);
	if (update == 0 && data->control)
		update_terminal_status(data, 0);
	update = (update + 1) % 10;
	data->event.rp_x = 0;
	data->event.rp_y = 0;
	return (1);
}
