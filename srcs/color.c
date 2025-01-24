/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 11:16:47 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/15 16:03:24 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* -------------------------------------------------------------------------- */
/* Init function for the color. It is only used at the init, and sets the     */
/* color to its corresponding color's height, or to whatever color was        */
/* specified in the map.                                                      */
/* -------------------------------------------------------------------------- */
void	set_color(t_obj *obj)
{
	int		i;
	int		j;
	t_col	col1;
	t_col	col2;
	float	percent;

	if (obj->mat.col)
		return ;
	i = -1;
	while (++i < obj->mat.len)
	{
		j = -1;
		while (++j < obj->mat.wid)
		{
			percent = (float)obj->mat.matrix[i][j];
			if (percent > 0 && obj->max_h)
				percent /= (obj->max_h);
			else if (percent < 0 && obj->min_h)
				percent /= (-obj->min_h);
			chose_color(&col1, &col2, &percent);
			obj->mat.color[i][j] = calc_color((t_col){col1.re + (col2.re
						- col1.re) * percent, col1.gr + (col2.gr - col1.gr)
					* percent, col1.bl + (col2.bl - col1.bl) * percent});
		}
	}
}

/* -------------------------------------------------------------------------- */
/* Function used to do an interpolation between two points' color.            */
/* -------------------------------------------------------------------------- */
t_col	get_grad(t_col start, t_col end, float percent)
{
	t_col	color;
	t_col	col1;
	t_col	col2;

	if (percent <= 0)
		return (start);
	col1 = (t_col){start.re, start.gr, start.bl};
	col2 = (t_col){end.re, end.gr, end.bl};
	color.re = col1.re + (col2.re - col1.re) * percent;
	color.gr = col1.gr + (col2.gr - col1.gr) * percent;
	color.bl = col1.bl + (col2.bl - col1.bl) * percent;
	return (color);
}

/* -------------------------------------------------------------------------- */
/* Function used to get the color of a point and adding its gradient to       */
/* black if we are in perspective.                                            */
/* -------------------------------------------------------------------------- */
void	get_color(t_data *data, t_line *line, t_point start, t_point end)
{
	float	percent;

	if (!data->proj)
	{
		line->start.col = rev_calc_color(data->obj.mat.color[start.y][start.x]);
		line->end.col = rev_calc_color(data->obj.mat.color[end.y][end.x]);
	}
	else
	{
		percent = pow((float)line->start.z / data->modif.f_plane,
				data->modif.fog);
		line->start.col = get_grad(rev_calc_color(data->obj.mat.color[start.y]
				[start.x]), (t_col){0x00, 0x00, 0x00}, percent);
		percent = pow((float)line->end.z / data->modif.f_plane,
				data->modif.fog);
		line->end.col = get_grad(rev_calc_color(data->obj.mat.color[end.y]
				[end.x]), (t_col){0x00, 0x00, 0x00}, percent);
	}
}
