/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:12:54 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/15 17:11:28 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* -------------------------------------------------------------------------- */
/* Function used to retrieve the data structure.                              */
/* -------------------------------------------------------------------------- */
t_data	*get_data(void)
{
	static t_data	data;

	return (&data);
}

/* -------------------------------------------------------------------------- */
/* Function used to create the loops needed by the mlx.                       */
/* 2 is for the key down event.                                               */
/* 3 is for the key up event.                                                 */
/* 4 is for the mouse button down event.                                      */
/* 5 is for the mouse button up event.                                        */
/* 6 is for the mouse move event event.                                       */
/* 17 is for the destroy event.                                               */
/* -------------------------------------------------------------------------- */
void	loop(void)
{
	t_data	*data;

	data = get_data();
	mlx_hook(data->win, 2, 1L << 0, key_down, data);
	mlx_hook(data->win, 3, 1L << 1, key_up, data);
	mlx_hook(data->win, 4, 1L << 2, mouse_down, data);
	mlx_hook(data->win, 5, 1L << 3, mouse_up, data);
	mlx_hook(data->win, 6, 1L << 6, mouse_move, data);
	mlx_hook(data->win, 17, 0, mlx_close, data);
	mlx_loop_hook(data->mlx, event_loop, data);
	mlx_loop(data->mlx);
}

/* -------------------------------------------------------------------------- */
/* Function used to start everything, while making sure the user doesnt give  */
/* any map, or gives more than one map.                                       */
/* -------------------------------------------------------------------------- */
int	main(int ac, char **av)
{
	t_data	*data;

	if (ac != 2)
		ft_perror(2, 0, NULL);
	data = get_data();
	init_data(data, &av[1]);
	loop();
}
