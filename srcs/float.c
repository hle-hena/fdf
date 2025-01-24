/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 11:37:58 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/15 17:06:28 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* -------------------------------------------------------------------------- */
/* Function used to round a float value, in order to try to avoid float       */
/* inprecision errors                                                         */
/* -------------------------------------------------------------------------- */
float	round_float(float value, int n)
{
	float	factor;

	factor = pow(10, n);
	return (roundf(value * factor) / factor);
}

/* -------------------------------------------------------------------------- */
/* Function used to round a vector, in order to try to avoid float            */
/* inprecision errors                                                         */
/* -------------------------------------------------------------------------- */
void	round_vec(t_vec *vec)
{
	vec->x = round_float(vec->x, 5);
	vec->y = round_float(vec->y, 5);
	vec->z = round_float(vec->z, 5);
}
