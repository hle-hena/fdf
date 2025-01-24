/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:35:11 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/15 16:46:52 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* -------------------------------------------------------------------------- */
/* Start function of the Brehensam algorithm, which decides if I have to      */
/*draw a high or a low line based on the positon of the points.               */
/* -------------------------------------------------------------------------- */
void	draw_line(t_data *data, t_point start, t_point end)
{
	if (ft_abs(end.y - start.y) < ft_abs(end.x - start.x))
	{
		if (start.x > end.x)
			return (draw_low(data, end, start));
		return (draw_low(data, start, end));
	}
	if (start.y > end.y)
		return (draw_high(data, end, start));
	return (draw_high(data, start, end));
}

/* -------------------------------------------------------------------------- */
/* Function used to calculate and create the points of a line, base on their  */
/* position in the 2D map.                                                    */
/* The function vec transforms the object's coordinates into world            */
/* coordinates. The calc_point function give the new coordinates after        */
/* applying the projection matrix. The move_point function handle the cliping */
/* of the lines. Finaly, the get_color func retrieves the color of the points.*/
/* -------------------------------------------------------------------------- */
int	create_line(t_data *data, t_point start, t_point end, int col)
{
	t_line	line;
	t_vec	v_start;
	t_vec	v_end;

	v_start = vec(data->obj, data->wld, start);
	v_end = vec(data->obj, data->wld, end);
	if (!calc_point(data, &line, &v_start, &v_end))
		return (0);
	if (!move_point(data, &line.start, &line.end))
		return (0);
	if (col == 0)
	{
		line.start.col = (t_col){0, 0, 0};
		line.end.col = (t_col){0, 0, 0};
	}
	else
		get_color(data, &line, start, end);
	draw_line(data, line.start, line.end);
	return (1);
}

/* -------------------------------------------------------------------------- */
/* Function used to draw the map in isometric, drawing each line one after    */
/* the other, in the order specified by the limits.                           */
/* The limits and start for the map are given in pt as follows :              */
/*   pt.x  : start index of the columns                                       */
/*   pt.y  : start index of the lines                                         */
/*   pt.z  : limit for the index of the lines (either 0 or the map len - 1)   */
/*   inc.x : the value to add to the line index to make the loop (1 or -1)    */
/*   inc.y : the value to add to the column index to make the loop (1 or -1)  */
/*   inc.z : limit for the index of the columns (either 0 or the map wid - 1) */
/* -------------------------------------------------------------------------- */
void	draw_iso(t_data *data, int color, t_point pt, t_point inc)
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
/* Function used to draw the map. To know which way we are looking, we can    */
/* look at the world's base and conclude the following :                      */
/*   If the k.z value is greater than 0, we are looking from the top of the   */
/*   object, otherwise we are under it.                                       */
/*   If the k.y value is equal to 0, we are looking directly from the top of  */
/*   the map. If it negative, we are looking "backward", and if it is         */
/*   positive, we are looking "forward". To understand that forward/backward  */
/*   thing, just think of how you see your world. This way of seeing forward. */
/*   Finaly, we look at the i vector, while multiplying both its x and y by   */
/*   the sign of side, and multiplying its y by the sign of up, and can       */
/*   conclude that :                                                          */
/*     If i.x is positive, we are looking up the y axis                       */
/*     If i.y is positive, we are looking up the x axis                       */
/*   We then call the appropriated function, with its corresponding value.    */
/* -------------------------------------------------------------------------- */
void	draw_map(t_data *data, int color)
{
	int	up;
	int	side;

	if (data->proj)
		return (draw_persp(data, color));
	up = ft_tern_int(data->wld.base.k.z >= 0, 1, -1);
	side = ft_tern_int(data->wld.base.k.y <= 0, 1, -1);
	data->obj.r_ori = vec(data->obj, data->wld, data->obj.wld_ori);
	if (data->wld.base.i.x * side >= 0
		&& data->wld.base.i.y * side * up >= 0)
		draw_iso(data, color, (t_point){0, 0, data->obj.mat.len, (t_col){0}},
			(t_point){1, 1, data->obj.mat.wid, (t_col){0}});
	else if (data->wld.base.i.x * side > 0
		&& data->wld.base.i.y * side * up < 0)
		draw_iso(data, color, (t_point){data->obj.mat.wid - 1, 0,
			data->obj.mat.len, (t_col){0}}, (t_point){-1, 1, -1, (t_col){0}});
	else if (data->wld.base.i.x * side < 0
		&& data->wld.base.i.y * side * up > 0)
		draw_iso(data, color, (t_point){0, data->obj.mat.len - 1, -1,
			(t_col){0}}, (t_point){1, -1, data->obj.mat.wid, (t_col){0}});
	else if (data->wld.base.i.x * side < 0
		&& data->wld.base.i.y * side * up < 0)
		draw_iso(data, color, (t_point){data->obj.mat.wid - 1, data->obj.mat.len
			- 1, -1, (t_col){0}}, (t_point){-1, -1, -1, (t_col){0}});
}
