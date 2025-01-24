/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 11:43:53 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/15 16:00:32 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* -------------------------------------------------------------------------- */
/* Function used to convert an rbg structure col into an int used by          */
/* the mlx.                                                                   */
/* -------------------------------------------------------------------------- */
int	calc_color(t_col col)
{
	return ((col.re << 16) | (col.gr << 8) | col.bl);
}

/* -------------------------------------------------------------------------- */
/* Function used to convert an int into an rgb structure used by me.          */
/* -------------------------------------------------------------------------- */
t_col	rev_calc_color(int col)
{
	return ((t_col){col >> 16 & 0xFF, col >> 8 & 0xFF, col & 0xFF});
}

/* -------------------------------------------------------------------------- */
/* Functions used to chose which color to put for the gradient, base on the   */
/* percentage of the height of the point chosen.                              */
/* -------------------------------------------------------------------------- */
void	chose_color_2(t_col *col1, t_col *col2, float *percent)
{
	*percent *= -1;
	if (*percent <= 0.5)
	{
		*col1 = (t_col){0x80, 0xFF, 0xBA};
		*col2 = (t_col){0x41, 0xF9, 0xDB};
		*percent *= 2;
	}
	else
	{
		*col1 = (t_col){0x41, 0xF9, 0xDB};
		*col2 = (t_col){0x00, 0xF2, 0xFF};
		*percent = (*percent - 0.5) * 2;
	}
}

void	chose_color(t_col *col1, t_col *col2, float *percent)
{
	if (*percent == 0)
	{
		*col1 = (t_col){0xFF, 0xFF, 0xFF};
		*col2 = (t_col){0xFF, 0xFF, 0xFF};
		return ;
	}
	if (*percent >= 0)
	{
		if (*percent <= 0.5)
		{
			*col1 = (t_col){0xFF, 0xFB, 0x7D};
			*col2 = (t_col){0xFF, 0xA5, 0xB7};
			*percent *= 2;
		}
		else
		{
			*col1 = (t_col){0xFF, 0xA5, 0xB7};
			*col2 = (t_col){0xFF, 0x4B, 0xF3};
			*percent = (*percent - 0.5) * 2;
		}
		return ;
	}
	chose_color_2(col1, col2, percent);
}
