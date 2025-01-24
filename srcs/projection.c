/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 13:58:00 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/16 11:02:30 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* -------------------------------------------------------------------------- */
/* Function used to change the points of the line to make an isometric        */
/* projection. To do so, we simply only keep the x and y coordinate, and move */
/* the center to half the wid and the len of the window.                      */
/* -------------------------------------------------------------------------- */
int	get_iso(t_data *data, t_line *line, t_vec *start, t_vec *end)
{
	line->start = (t_point){start->x + (data->win_wid / 2),
		start->y + (data->win_len / 2), 100, (t_col){0, 0, 0}};
	line->end = (t_point){end->x + (data->win_wid / 2),
		end->y + (data->win_len / 2), 100, (t_col){0, 0, 0}};
	return (1);
}

/* -------------------------------------------------------------------------- */
/* Function used to change the points of a line to make a perspective         */
/* projection. To do so, we first ignore the line if both points are outside  */
/* the view frustrum. We then handle the cliping outside of the view          */
/* frustrum. Finaly we multiply the x and y coordinates by their respective   */
/* fov scaling, divide this result by the z value of the point, and place     */
/* back the center to half the wid and the len of the window.                 */
/* -------------------------------------------------------------------------- */
int	get_persp(t_data *data, t_line *line, t_vec *start, t_vec *end)
{
	float	fov_scale_x;
	float	fov_scale_y;

	if ((start->z < data->wld.cam.n_plane && end->z < data->wld.cam.n_plane)
		|| (start->z > data->modif.f_plane && end->z > data->modif.f_plane))
		return (0);
	fov_scale_x = data->win_wid
		/ (2.0f * tan((data->modif.fov * (M_PI / 180)) / 2.0f));
	fov_scale_y = data->win_len
		/ (2.0f * tan((data->modif.fov * (M_PI / 180)) / 2.0f));
	if (start->z < data->wld.cam.n_plane)
		change_point(start, *end, data->wld.cam.n_plane);
	else if (end->z < data->wld.cam.n_plane)
		change_point(end, *start, data->wld.cam.n_plane);
	if (start->z > data->modif.f_plane)
		change_point(start, *end, data->modif.f_plane);
	else if (end->z > data->modif.f_plane)
		change_point(end, *start, data->modif.f_plane);
	line->start = (t_point){(start->x * fov_scale_x) / start->z + (data->win_wid
			/ 2), (start->y * fov_scale_y) / start->z + (data->win_len / 2),
		start->z, (t_col){0, 0, 0}};
	line->end = (t_point){(end->x * fov_scale_x) / end->z + (data->win_wid / 2),
		(end->y * fov_scale_y) / end->z + (data->win_len / 2),
		end->z, (t_col){0, 0, 0}};
	return (1);
}

/* -------------------------------------------------------------------------- */
/* Function used to chose between the two projection, and return its          */
/* return value.                                                              */
/* -------------------------------------------------------------------------- */
int	calc_point(t_data *data, t_line *line, t_vec *start, t_vec *end)
{
	if (data->proj == 0)
		return (get_iso(data, line, start, end));
	else if (data->proj == 1)
		return (get_persp(data, line, start, end));
	return (0);
}
