/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:26:10 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/16 11:31:38 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* -------------------------------------------------------------------------- */
/* Function used to delete both the matrix containing the heights and the one */
/* containing the color.                                                      */
/* -------------------------------------------------------------------------- */
void	del_matrix(t_data *data)
{
	int	i;

	if (data->obj.mat.matrix)
	{
		i = 0;
		while (data->obj.mat.matrix[i])
			i++;
		ft_free_tab((void **)data->obj.mat.matrix, i);
	}
	if (data->obj.mat.color)
	{
		i = 0;
		while (data->obj.mat.color[i])
			i++;
		ft_free_tab((void **)data->obj.mat.color, i);
	}
}

/* -------------------------------------------------------------------------- */
/* Function called to delete everything from the mlx.                         */
/* -------------------------------------------------------------------------- */
int	mlx_del(t_data *data)
{
	if (!data)
		data = get_data();
	del_matrix(data);
	if (data->mlx && data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	return (0);
}

/* -------------------------------------------------------------------------- */
/* Function used to write an error message based on an error code into the    */
/* stderr                                                                     */
/* -------------------------------------------------------------------------- */
void	put_error_code(int code)
{
	if (code == 1)
		ft_putstr_fd("Something went wrong.", 2);
	else if (code == 2)
		ft_putstr_fd("Wrong argument given to the program.", 2);
	else if (code == 3)
		ft_putstr_fd("Error happened during a malloc.", 2);
	else if (code == 4)
		ft_putstr_fd("Something went wrong during the parsing of the args.", 2);
}

/* -------------------------------------------------------------------------- */
/* Function used to update the status window, and put an error message.       */
/* -------------------------------------------------------------------------- */
void	ft_perror(int error_code, int clean, char *custom_mess)
{
	if (clean)
		ft_putendl_fd("What even happened there ???", 2);
	else
	{
		ft_printf("\033[0;36m/**********************************/\n");
		ft_printf(
			"/*  FDF STATUS : \033[38;2;255;0;0mDEAD\033[0;36m\
             */\n");
		ft_printf("/**********************************/\n");
		ft_printf("/* Current fps : ---              */\n");
		ft_printf("/**********************************/\n");
		ft_printf("/* Current modifier : ----------  */\n");
		ft_printf("/*     value : ---------------    */\n");
		ft_printf("/**********************************/\n");
		ft_printf("/* Realistic movement :           */\n");
		ft_printf("/*     ------------               */\n");
		ft_printf("/**********************************/\n\033[0;0m");
		ft_putstr_fd("\033[0;31m", 2);
		if (error_code)
			put_error_code(error_code);
		else
			ft_putstr_fd(custom_mess, 2);
		ft_putendl_fd("\033[0;0m", 2);
	}
	exit(0);
}

/* -------------------------------------------------------------------------- */
/* Function used to update the status window and end the program.             */
/* -------------------------------------------------------------------------- */
void	ft_pend_prog(void)
{
	clear_lines(11);
	ft_printf("\033[0;36m/**********************************/\n");
	ft_printf(
		"/*  FDF STATUS : \033[38;2;0;255;0mENDED\033[0;36m            */\n");
	ft_printf("/**********************************/\n");
	ft_printf("/* Current fps : ---              */\n");
	ft_printf("/**********************************/\n");
	ft_printf("/* Current modifier : ----------  */\n");
	ft_printf("/*     value : ---------------    */\n");
	ft_printf("/**********************************/\n");
	ft_printf("/* Realistic movement :           */\n");
	ft_printf("/*     ------------               */\n");
	ft_printf("/**********************************/\n\033[0;0m");
	exit(0);
}
