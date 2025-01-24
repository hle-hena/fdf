/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 12:49:06 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/16 11:31:21 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* -------------------------------------------------------------------------- */
/* Function used to clean lines lines.                                        */
/* -------------------------------------------------------------------------- */
void	clear_lines(int lines)
{
	int	i;

	i = 0;
	while (i++ < lines)
	{
		ft_printf("\033[1A");
		ft_printf("\033[K");
	}
}

/* -------------------------------------------------------------------------- */
/* Function used to retrieve the name of the current modifier.                */
/* -------------------------------------------------------------------------- */
char	*get_modif(t_data *data)
{
	if (data->modif.ind == 0)
		return ("fog");
	if (data->modif.ind == 1)
		return ("movement");
	if (data->modif.ind == 2)
		return ("rotation");
	if (data->modif.ind == 3)
		return ("fov");
	if (data->modif.ind == 4)
		return ("far plane");
	if (data->modif.ind == 5)
		return ("height");
	return (NULL);
}

/* -------------------------------------------------------------------------- */
/* Function used to retrieve the value of the current modifier.               */
/* -------------------------------------------------------------------------- */
int	get_modif_val(t_data *data)
{
	if (data->modif.ind == 0)
		return (data->modif.fog);
	if (data->modif.ind == 1)
		return (data->modif.mo_speed);
	if (data->modif.ind == 2)
		return (data->modif.rot_speed);
	if (data->modif.ind == 3)
		return (data->modif.fov);
	if (data->modif.ind == 4)
		return (data->modif.f_plane);
	if (data->modif.ind == 5)
		return (data->modif.height);
	return (0);
}

/* -------------------------------------------------------------------------- */
/* Function used to update the fps, the modifier, and the r_move value.       */
/* -------------------------------------------------------------------------- */
void	update_terminal_status(t_data *data, int init)
{
	if (!init)
		clear_lines(11);
	ft_printf("\033[0;36m/**********************************/\n");
	ft_printf("/*  FDF STATUS : \033[0;33mRUNNING\033[0;36m          */\n");
	ft_printf("/**********************************/\n");
	ft_printf("/* Current fps : \033[0;33m%-3d\033[0;36m              */\n",
		data->fps);
	ft_printf("/**********************************/\n");
	ft_printf("/* Current modifier : \033[0;33m%-10s\033[0;36m  */\n",
		get_modif(data));
	ft_printf("/*     value : \033[0;33m%-15d\033[0;36m    */\n",
		get_modif_val(data));
	ft_printf("/**********************************/\n");
	ft_printf("/* Realistic movement :           */\n");
	ft_printf("/*     \033[0;33m%-12s\033[0;36m               */\n",
		ft_tern(data->modif.r_move, "Activated", "De-activated"));
	ft_printf("/**********************************/\n\033[0;0m");
}
