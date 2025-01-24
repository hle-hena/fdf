/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_euler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 15:25:20 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/16 11:06:20 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* -------------------------------------------------------------------------- */
/* Function used to multiply a vector by the 3D rotation matrix around the y, */
/* x, and finaly z axis.                                                      */
/* -------------------------------------------------------------------------- */
void	do_rot_yxz(t_vec *vec, t_trig rot_y, t_trig rot_x, t_trig rot_z)
{
	float	temp_x;
	float	temp_y;
	float	temp_z;

	temp_x = vec->x * (rot_y.cos * rot_z.cos)
		+ vec->y * (rot_x.sin * rot_y.sin * rot_z.cos - rot_x.cos * rot_z.sin)
		+ vec->z * (rot_x.cos * rot_y.sin * rot_z.cos + rot_x.sin * rot_z.sin);
	temp_y = vec->x * (rot_y.cos * rot_z.sin)
		+ vec->y * (rot_x.sin * rot_y.sin * rot_z.sin + rot_x.cos * rot_z.cos)
		+ vec->z * (rot_x.cos * rot_y.sin * rot_z.sin - rot_x.sin * rot_z.cos);
	temp_z = vec->x * (-rot_y.sin)
		+ vec->y * (rot_x.sin * rot_y.cos)
		+ vec->z * (rot_x.cos * rot_y.cos);
	vec->x = temp_x;
	vec->y = temp_y;
	vec->z = temp_z;
	round_vec(vec);
}

/* -------------------------------------------------------------------------- */
/* Function used to block the rotation around the x axis (pitch). If the      */
/* rotation to be aplied makes the rotation greater than the limit set, we    */
/* set the rotaion back to the limit, and remove the excess in the rot value. */
/* -------------------------------------------------------------------------- */
void	block_rot(float *val, float *rot, int axis)
{
	if (axis == 1)
	{
		if (*val >= 160 * (M_PI / 180))
		{
			*rot -= ((180 * *val) / M_PI - 160) * (M_PI / 180);
			*val = 160 * (M_PI / 180);
		}
		else if (*val <= 20 * (M_PI / 180))
		{
			*rot -= ((180 * *val) / M_PI - 20) * (M_PI / 180);
			*val = 20 * (M_PI / 180);
		}
	}
}
