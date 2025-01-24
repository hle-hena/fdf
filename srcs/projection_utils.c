/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 12:04:40 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/16 10:52:24 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* -------------------------------------------------------------------------- */
/* Function used to interpolate between two points, in order to keep both     */
/* points of a line in the screen. To do so, we use the parametric equation   */
/* of the line, and calculate a new parameter. If the parameter is greater    */
/* than 1 or smaller than 0, it means that the line is completly outside of   */
/* the screen, therfore we return 1, meaning that the line must not be drawn. */
/* -------------------------------------------------------------------------- */
int	move_point_w(t_data *data, t_point *change, t_point other, int bord)
{
	int		border;
	float	param;
	t_point	n_point;

	if (other.x == change->x)
		return (1);
	if (bord)
		border = 0;
	else
		border = data->win_wid;
	param = (float)(border - change->x) / (other.x - change->x);
	if (param < 0 || param > 1)
		return (1);
	n_point = (t_point){border,
		change->y + param * (other.y - change->y),
		change->z + param * (other.z - change->z),
		get_grad(change->col, other.col, param)};
	*change = n_point;
	return (0);
}

/* -------------------------------------------------------------------------- */
/* Function used to do the same thing as the one above, except that it is     */
/* handling the vectical cliping.                                             */
/* -------------------------------------------------------------------------- */
int	move_point_l(t_data *data, t_point *change, t_point other, int bord)
{
	int		border;
	float	param;
	t_point	n_point;

	if (other.y == change->y)
		return (1);
	if (bord)
		border = 0;
	else
		border = data->win_len;
	param = (float)(border - change->y) / (other.y - change->y);
	if (param > 1 || param < 0)
		return (1);
	n_point = (t_point){change->x + param * (other.x - change->x),
		border,
		change->z + param * (other.z - change->z),
		get_grad(change->col, other.col, param)};
	*change = n_point;
	return (0);
}

/* -------------------------------------------------------------------------- */
/* Function used to decide if it is needed to move a point. We need to move   */
/* it only if one or both points are outside of the screen. If we cannot move */
/* the point back into the screen, the line is completly outside and should   */
/* not be drawn, therefore we return 0.                                       */
/* -------------------------------------------------------------------------- */
int	move_point(t_data *data, t_point *start, t_point *end)
{
	if (start->x > data->win_wid || start->x < 0)
		if (move_point_w(data, start, *end, start->x < 0))
			return (0);
	if (end->x > data->win_wid || end->x < 0)
		if (move_point_w(data, end, *start, end->x < 0))
			return (0);
	if (start->y > data->win_len || start->y < 0)
		if (move_point_l(data, start, *end, start->y < 0))
			return (0);
	if (end->y > data->win_len || end->y < 0)
		if (move_point_l(data, end, *start, end->y < 0))
			return (0);
	return (1);
}

/* -------------------------------------------------------------------------- */
/* Move a point into the view frustrum by using the line's paramtric equation */
/* and setting the z (depth) value to whatever we want (either the far plane  */
/* or the near plane).                                                        */
/* -------------------------------------------------------------------------- */
void	change_point(t_vec *change, t_vec other, int z)
{
	float	param;
	t_vec	n_point;

	param = (float)(z - change->z) / (other.z - change->z);
	n_point = (t_vec){change->x + param * (other.x - change->x),
		change->y + param * (other.y - change->y), z};
	*change = n_point;
}

/* -------------------------------------------------------------------------- */
/* Function used to switch between the different projections.                 */
/* If we are going into perspective, we reverse the j vector in order to      */
/* prevent a flipping of the world. We also fix the scale to 15. Finaly, we   */
/* place the camera to the edge of the obj, looking a bit down.               */
/* If we are going into isometric, we zoom back in, and make the camera look  */
/* the closest possible to the subject reference.                             */
/* -------------------------------------------------------------------------- */
void	go_to_proj(t_data *data)
{
	if (data->proj)
	{
		data->wld.init.j = (t_vec){0, -1, 0};
		data->wld.cam.init.j = (t_vec){0, -1, 0};
		data->wld.cam.rot = (t_vec){115 * (M_PI / 180),
			0 * (M_PI / 180), 0};
		data->wld.cam.scale = (15);
		data->wld.cam.ori = (t_vec){0, data->obj.mat.len * (15), 10 * (15)};
		look_at(&data->wld.base, data->wld.init, data->wld.cam.rot);
		look_at(&data->wld.cam.base, data->wld.cam.init, data->wld.cam.rot);
	}
	else if (!data->proj)
	{
		data->wld.init.j = (t_vec){0, 1, 0};
		data->wld.cam.init.j = (t_vec){0, 1, 0};
		data->wld.cam.rot = (t_vec){
			24 * (M_PI / 180),
			-24 * (M_PI / 180),
			37 * (M_PI / 180)
		};
		data->wld.cam.scale = data->wld.init_scale;
		data->wld.cam.ori = (t_vec){0, 0, 0};
		look_at(&data->wld.base, data->wld.init, data->wld.cam.rot);
		look_at(&data->wld.cam.base, data->wld.cam.init, data->wld.cam.rot);
	}
}
