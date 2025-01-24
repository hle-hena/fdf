/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_persp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:37:44 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/15 16:36:46 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* -------------------------------------------------------------------------- */
/* Function used to retrieve the camera's position in the map.                */
/* It is an unused func at the moment.                                        */
/* -------------------------------------------------------------------------- */
t_point	get_obj_coo(t_wld wld, t_obj obj)
{
	t_point	cam_coo;
	int		scale_factor;

	scale_factor = obj.scale * wld.cam.scale * 2;
	cam_coo.x = (wld.cam.ori.x / scale_factor) - obj.wld_ori.x
		+ obj.mat_ori.x + 0.5;
	cam_coo.y = (wld.cam.ori.y / scale_factor) - obj.wld_ori.y
		+ obj.mat_ori.y + 0.5;
	cam_coo.z = (wld.cam.ori.z / scale_factor) - obj.wld_ori.z
		+ obj.mat_ori.z + 0.5;
	return (cam_coo);
}

/* -------------------------------------------------------------------------- */
/* Function used to draw the map in perspective, looking down or up the       */
/* y axis, drawing each line one after the other, in the order specified by   */
/* the limits.                                                                */
/* The limits and start for the map are given in pt as follows :              */
/*   pt.x  : start index of the columns                                       */
/*   pt.y  : start index of the lines                                         */
/*   pt.z  : limit for the index of the lines (either 0 or the map len - 1)   */
/*   inc.x : the value to add to the line index to make the loop (1 or -1)    */
/*   inc.y : the value to add to the column index to make the loop (1 or -1)  */
/*   inc.z : limit for the index of the columns (either 0 or the map wid - 1) */
/* -------------------------------------------------------------------------- */
void	draw_for(t_data *data, int color, t_point pt, t_point inc)
{
	int	start;

	start = pt.x;
	while (pt.y != pt.z)
	{
		pt.x = start;
		while (pt.x != inc.z)
		{
			if (pt.y != data->obj.mat.len - 1)
				create_line(data, (t_point){pt.x, pt.y,
					data->obj.mat.matrix[pt.y][pt.x], (t_col){0}}, (t_point){
					pt.x, pt.y + 1, data->obj.mat.matrix[pt.y + 1][pt.x],
					(t_col){0}}, color);
			if (pt.x != data->obj.mat.wid - 1)
				create_line(data, (t_point){pt.x, pt.y,
					data->obj.mat.matrix[pt.y][pt.x], (t_col){0}}, (t_point){
					pt.x + 1, pt.y, data->obj.mat.matrix[pt.y][pt.x + 1],
					(t_col){0}}, color);
			pt.x += inc.x;
		}
		pt.y += inc.y;
	}
	if (color)
		mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

/* -------------------------------------------------------------------------- */
/* Function used to draw the map in perspective, looking down or up the       */
/* x axis, drawing each column one after the other, in the order specified by */
/* the limits.                                                                */
/* The limits and start for the map are given in pt as follows :              */
/*   pt.x  : start index of the columns                                       */
/*   pt.y  : start index of the lines                                         */
/*   pt.z  : limit for the index of the lines (either 0 or the map len - 1)   */
/*   inc.x : the value to add to the line index to make the loop (1 or -1)    */
/*   inc.y : the value to add to the column index to make the loop (1 or -1)  */
/*   inc.z : limit for the index of the columns (either 0 or the map wid - 1) */
/* -------------------------------------------------------------------------- */
void	draw_side(t_data *data, int color, t_point pt, t_point inc)
{
	int	start;

	start = pt.y;
	while (pt.x != inc.z)
	{
		pt.y = start;
		while (pt.y != pt.z)
		{
			if (pt.y != data->obj.mat.len - 1)
				create_line(data, (t_point){pt.x, pt.y,
					data->obj.mat.matrix[pt.y][pt.x], (t_col){0}}, (t_point){
					pt.x, pt.y + 1, data->obj.mat.matrix[pt.y + 1][pt.x],
					(t_col){0}}, color);
			if (pt.x != data->obj.mat.wid - 1)
				create_line(data, (t_point){pt.x, pt.y,
					data->obj.mat.matrix[pt.y][pt.x], (t_col){0}}, (t_point){
					pt.x + 1, pt.y, data->obj.mat.matrix[pt.y][pt.x + 1],
					(t_col){0}}, color);
			pt.y += inc.y;
		}
		pt.x += inc.x;
	}
	if (color)
		mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

/* -------------------------------------------------------------------------- */
/* Function used to draw the map in perspective. To know which way we are     */
/* looking, we can look at the world's base x value of the the vectors i and  */
/* j, and conclude the following :                                            */
/*   If the i.x value is greater than 0.5, we are looking up the y axis.      */
/*   If the i.x value is smaller than -0.5, we are looking down the y axis.   */
/*   If the i.x value is between -0.5 and 0.5, but the j.x value is negative, */
/*   we are looking up the x axis.                                            */
/*   If the i.x value is between -0.5 and 0.5, but the j.x value is positive, */
/*   we are looking up the x axis.                                            */
/* We then call the appropriate function, with its corresponding value.       */
/* -------------------------------------------------------------------------- */
void	draw_persp(t_data *data, int color)
{
	data->obj.r_ori = vec(data->obj, data->wld, data->obj.wld_ori);
	if (data->wld.base.i.x >= 0.5)
		draw_for(data, color, (t_point){0, 0, data->obj.mat.len, (t_col){0}},
			(t_point){1, 1, data->obj.mat.wid, (t_col){0}});
	else if (data->wld.base.i.x > -0.5 && data->wld.base.i.x < 0.5
		&& data->wld.base.j.x > 0)
		draw_side(data, color, (t_point){data->obj.mat.wid - 1, 0,
			data->obj.mat.len, (t_col){0}}, (t_point){-1, 1, -1, (t_col){0}});
	else if (data->wld.base.i.x > -0.5 && data->wld.base.i.x < 0.5
		&& data->wld.base.j.x < 0)
		draw_side(data, color, (t_point){0, data->obj.mat.len - 1, -1,
			(t_col){0}}, (t_point){1, -1, data->obj.mat.wid, (t_col){0}});
	else if (data->wld.base.i.x <= -0.5)
		draw_for(data, color, (t_point){data->obj.mat.wid - 1, data->obj.mat.len
			- 1, -1, (t_col){0}}, (t_point){-1, -1, -1, (t_col){0}});
}
