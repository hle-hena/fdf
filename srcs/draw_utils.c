/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:22:35 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/15 16:27:58 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* -------------------------------------------------------------------------- */
/* Function used to know if a point is within the image, in order to          */
/* avoid a segfault.                                                          */
/* -------------------------------------------------------------------------- */
int	point_is_in_fov(t_data *data, t_point point)
{
	if (point.x < data->win_wid && point.x >= 0
		&& point.y < data->win_len
		&& point.y >= 0)
		return (1);
	return (0);
}

/* -------------------------------------------------------------------------- */
/* Function used to mimic the mlx_put_pixel func, but using the image of the  */
/* mlx in order to have a faster draw function.                               */
/* -------------------------------------------------------------------------- */
void	put_pixel(t_data *data, t_point point, int color)
{
	int	*img;
	int	temp;
	int	size_line;

	img = (int *)mlx_get_data_addr(data->img, &temp, &size_line, &temp);
	img[point.y * data->win_wid + point.x] = color;
}

/* -------------------------------------------------------------------------- */
/* Function used within the Brehensam algorithm. It is used to know if the    */
/* slope goes up by a pixel or not.                                           */
/* -------------------------------------------------------------------------- */
void	calc_err(int *err, int *slope, int da, int db)
{
	if (*err > 0)
	{
		*slope += ft_tern_int(da < 0, -1, 1);
		*err += 2 * (ft_abs(da) - db);
	}
	else
		*err += 2 * ft_abs(da);
}

/* -------------------------------------------------------------------------- */
/* Function used within the Brehensam algorithm to draw every line with a     */
/* slope's coeficient greater than 1 or smaller than -1.                      */
/* -------------------------------------------------------------------------- */
void	draw_high(t_data *data, t_point start, t_point end)
{
	int		dx;
	int		dy;
	int		err;
	float	percent;
	t_point	curr;

	dx = end.x - start.x;
	dy = end.y - start.y;
	err = 2 * ft_abs(dx) - dy;
	percent = 0;
	curr = (t_point){start.x, start.y, 0, (t_col){0}};
	while (curr.y <= end.y)
	{
		if (point_is_in_fov(data, curr))
			put_pixel(data, curr,
				calc_color(get_grad(start.col, end.col, percent)));
		calc_err(&err, &curr.x, dx, dy);
		curr.y += 1;
		if (calc_color(start.col) != calc_color(end.col))
			percent += (float)1 / dy;
	}
}

/* -------------------------------------------------------------------------- */
/* Function used within the Brehensam algorithm to draw every line with a     */
/* slope's coeficient between 1 and -1.                                       */
/* -------------------------------------------------------------------------- */
void	draw_low(t_data *data, t_point start, t_point end)
{
	int		dx;
	int		dy;
	int		err;
	float	percent;
	t_point	curr;

	dx = end.x - start.x;
	dy = end.y - start.y;
	err = 2 * ft_abs(dy) - dx;
	percent = 0;
	curr = (t_point){start.x, start.y, 0, (t_col){0}};
	while (curr.x <= end.x)
	{
		if (point_is_in_fov(data, curr))
			put_pixel(data, curr,
				calc_color(get_grad(start.col, end.col, percent)));
		calc_err(&err, &curr.y, dy, dx);
		curr.x += 1;
		if (calc_color(start.col) != calc_color(end.col))
			percent += (float)1 / dx;
	}
}
