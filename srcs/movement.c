/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 10:50:22 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/16 10:30:19 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* -------------------------------------------------------------------------- */
/* Function used to move the camera's z up or down, depending if Q or E is    */
/* clicked.                                                                   */
/* -------------------------------------------------------------------------- */
void	go_up(t_data *data, int sign)
{
	data->wld.cam.ori.z += sign * data->modif.mo_speed * (10);
}

/* -------------------------------------------------------------------------- */
/* Function used to move the camera along the y axis if in isometric          */
/* projection, otherwise based on the direction we are looking. If the r_move */
/* var is true, we also move along the z axis based on the pitch.             */
/* -------------------------------------------------------------------------- */
void	move_forward(t_data *data, int sign)
{
	if (!data->proj)
		data->wld.cam.ori.y += sign * (data->wld.cam.scale) * data->d_time
			* data->modif.mo_speed;
	else
	{
		data->wld.cam.ori.x += sign * (10) * data->d_time
			* data->wld.cam.base.i.z * data->modif.mo_speed;
		data->wld.cam.ori.y += -sign * (10) * data->d_time
			* data->wld.cam.base.i.x * data->modif.mo_speed;
		if (data->modif.r_move)
			data->wld.cam.ori.z += -sign * (10) * data->d_time
				* ((data->wld.cam.rot.x - (90 * (M_PI / 180))) / 2)
				* data->modif.mo_speed;
	}
}

/* -------------------------------------------------------------------------- */
/* Function used to move the camera along the x axis if in isometric          */
/* projection, otherwise based on the direction we are looking.               */
/* -------------------------------------------------------------------------- */
void	move_side(t_data *data, int sign)
{
	if (!data->proj)
		data->wld.cam.ori.x += -sign * (data->wld.cam.scale) * data->d_time
			* data->modif.mo_speed;
	else
	{
		data->wld.cam.ori.x += -sign * (10) * data->d_time
			* data->wld.cam.base.j.z * data->modif.mo_speed;
		data->wld.cam.ori.y += sign * (10) * data->d_time
			* data->wld.cam.base.j.x * data->modif.mo_speed;
	}
}
