/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 11:33:23 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/16 11:26:58 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* -------------------------------------------------------------------------- */
/* Functions used to make the camera looks in a direction.                    */
/* -------------------------------------------------------------------------- */
void	look_at(t_base *base, t_base init, t_vec rot)
{
	t_trig	rot_y;
	t_trig	rot_x;
	t_trig	rot_z;

	base->i = (t_vec){init.i.x, init.i.y, init.i.z};
	base->j = (t_vec){init.j.x, init.j.y, init.j.z};
	base->k = (t_vec){init.k.x, init.k.y, init.k.z};
	rot_y = (t_trig){sin(rot.y), cos(rot.y)};
	rot_x = (t_trig){sin(rot.x), cos(rot.x)};
	rot_z = (t_trig){sin(rot.z), cos(rot.z)};
	do_rot_yxz(&base->i, rot_y, rot_x, rot_z);
	do_rot_yxz(&base->j, rot_y, rot_x, rot_z);
	do_rot_yxz(&base->k, rot_y, rot_x, rot_z);
}

/* -------------------------------------------------------------------------- */
/* Function used to change the value of the rotation based on input given     */
/* into the var sign.                                                         */
/* -------------------------------------------------------------------------- */
void	add_rot(float *val, float *rot, float sign, int axis)
{
	t_data	*data;

	data = get_data();
	*val += data->modif.rot_speed * sign * (M_PI / 180) * data->d_time;
	*rot = data->modif.rot_speed * sign * (M_PI / 180) * data->d_time;
	if (*val >= (float)(2 * M_PI))
		*val = 0;
	else if (*val <= (float)-(2 * M_PI))
		*val = 0;
	*val = round_float(*val, 5);
	if (data->proj)
		block_rot(val, rot, axis);
}

/* -------------------------------------------------------------------------- */
/* Make the camera rotate along with the world. The camera base is primarly   */
/* used for the movement.                                                     */
/* -------------------------------------------------------------------------- */
void	rot_cam(t_base *base, float angle, t_vec axis)
{
	base->i = rot_vec(base->i, eul_to_quat(angle, axis));
	base->j = rot_vec(base->j, eul_to_quat(angle, axis));
	base->k = rot_vec(base->k, eul_to_quat(angle, axis));
	orthonormalize_base(base);
}

/* -------------------------------------------------------------------------- */
/* Function used to make the world rotate based on the input.                 */
/* -------------------------------------------------------------------------- */
void	do_rot(t_vec *cam_r, t_base *base, float sign, int axis)
{
	t_vec	rot;
	t_data	*data;
	float	angle;

	data = get_data();
	rot = (t_vec){1 * (axis == 1), 0, (1 * axis == 3)};
	if (data->proj && axis == 2)
		rot = base->k;
	else if (!data->proj && axis == 2)
		rot = (t_vec){-base->k.x, -base->k.y, -base->k.z};
	if (axis == 1)
		add_rot(&cam_r->x, &angle, sign, axis);
	else if (axis == 2)
		add_rot(&cam_r->y, &angle, sign, axis);
	else
		add_rot(&cam_r->z, &angle, sign, axis);
	base->i = rot_vec(base->i, eul_to_quat(angle, rot));
	base->j = rot_vec(base->j, eul_to_quat(angle, rot));
	base->k = rot_vec(base->k, eul_to_quat(angle, rot));
	orthonormalize_base(base);
	rot_cam(&data->wld.cam.base, angle, rot);
}
