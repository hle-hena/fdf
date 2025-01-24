/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_quaternion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 10:19:37 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/16 11:22:36 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* -------------------------------------------------------------------------- */
/* Function used to multply two quaternions.                                  */
/* -------------------------------------------------------------------------- */
t_quat	quat_mult(t_quat q1, t_quat q2)
{
	t_quat	result;

	result.w = q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z;
	result.x = q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y;
	result.y = q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x;
	result.z = q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w;
	return (result);
}

/* -------------------------------------------------------------------------- */
/* Function used to get a quaternion from an axis and a rotation.             */
/* -------------------------------------------------------------------------- */
t_quat	eul_to_quat(float angle, t_vec axis)
{
	t_quat	q;
	float	sin_half_angle;

	sin_half_angle = sin(angle / 2);
	q.w = cos(angle / 2);
	q.x = axis.x * sin_half_angle;
	q.y = axis.y * sin_half_angle;
	q.z = axis.z * sin_half_angle;
	return (q);
}

/* -------------------------------------------------------------------------- */
/* Function used to rotate a vector by a quaternion.                          */
/* -------------------------------------------------------------------------- */
t_vec	rot_vec(t_vec v, t_quat q)
{
	t_quat	qv;
	t_quat	q_conj;
	t_quat	q_res;

	qv = (t_quat){0, v.x, v.y, v.z};
	q_conj = (t_quat){q.w, -q.x, -q.y, -q.z};
	q_res = quat_mult(quat_mult(q, qv), q_conj);
	return ((t_vec){q_res.x, q_res.y, q_res.z});
}
