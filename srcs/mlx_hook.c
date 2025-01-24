/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 13:14:54 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/15 17:23:55 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* -------------------------------------------------------------------------- */
/* Function used to listen to key down event. This includes the movement, on  */
/* the keys {W, A, S, D}, the rotations on the keys {U, J, I, K, O, L},       */
/* switching between window size on the key {CTRL}, switching the current     */
/* modifier on the key {TAB} and increasing and decreasing it on the keys     */
/* {+, -}, switching to real movement on the key {SHIFT}, and finaly quiting  */
/* on the key {ECHAP}                                                         */
/* -------------------------------------------------------------------------- */
int	key_down(int keycode, t_data *data)
{
	if (keycode == 65307)
		mlx_close(data);
	else if (keycode == 65507)
		new_window(data);
	else if (keycode == 65289 && data->control)
		data->modif.ind = (data->modif.ind + 1) % 6;
	else if (keycode == 65505)
		data->modif.r_move = !data->modif.r_move;
	else if (keycode == 119 || keycode == 115)
		data->event.mo_f = (keycode == 119) * 1 + (keycode == 115) * -1;
	else if (keycode == 100 || keycode == 97)
		data->event.mo_s = (keycode == 100) * 1 + (keycode == 97) * -1;
	else if (keycode == 113 || keycode == 101)
		data->event.mo_u = (keycode == 113) * 1 + (keycode == 101) * -1;
	else if (keycode == 117 || keycode == 106)
		data->event.rot_x = (keycode == 117) * 1 + (keycode == 106) * -1;
	else if (keycode == 105 || keycode == 107)
		data->event.rot_y = (keycode == 105) * 1 + (keycode == 107) * -1;
	else if (keycode == 111 || keycode == 108)
		data->event.rot_z = (keycode == 111) * 1 + (keycode == 108) * -1;
	else if ((keycode == 45 || keycode == 61) && data->control)
		data->event.inc = (keycode == 61) * 1 + (keycode == 45) * -1;
	return (0);
}

/* -------------------------------------------------------------------------- */
/* Function used to block the key down event. This includes the movement, on  */
/* the keys {W, A, S, D}, the rotations on the keys {U, J, I, K, O, L},       */
/* switching between window size on the key {CTRL}, switching the current     */
/* modifier on the key {TAB} and increasing and decreasing it on the keys     */
/* {+, -}, switching to real movement on the key {SHIFT}, and finaly quiting  */
/* on the key {ECHAP}                                                         */
/* -------------------------------------------------------------------------- */
int	key_up(int keycode, t_data *data)
{
	if (keycode == 32)
	{
		draw_map(data, 0);
		data->proj = !data->proj;
		go_to_proj(data);
		draw_map(data, 1);
	}
	if (keycode == 119 || keycode == 115)
		data->event.mo_f = 0;
	else if (keycode == 100 || keycode == 97)
		data->event.mo_s = 0;
	else if (keycode == 113 || keycode == 101)
		data->event.mo_u = 0;
	else if (keycode == 117 || keycode == 106)
		data->event.rot_x = 0;
	else if (keycode == 105 || keycode == 107)
		data->event.rot_y = 0;
	else if (keycode == 111 || keycode == 108)
		data->event.rot_z = 0;
	else if (keycode == 45 || keycode == 61)
		data->event.inc = 0;
	return (0);
}

/* -------------------------------------------------------------------------- */
/* Function used to listen to mouse down event, wich includes scaling with    */
/* the mouse scroll and allowing the camera to move around.                   */
/* -------------------------------------------------------------------------- */
int	mouse_down(int button, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	if (button == 1)
		data->event.lock = 1;
	if (button == 4 && data->proj == 0)
		data->event.sc += 1;
	else if (button == 5 && data->wld.cam.scale != 1 && data->proj == 0)
		data->event.sc -= 1;
	return (1);
}

/* -------------------------------------------------------------------------- */
/* Function used to prevent from rotating the camera when we are not clicking */
/* with the mouse.                                                            */
/* -------------------------------------------------------------------------- */
int	mouse_up(int button, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	if (button == 1)
		data->event.lock = 0;
	return (1);
}

/* -------------------------------------------------------------------------- */
/* Function used to rotate the camera when in perspective. It also teleports  */
/* the mouse to the side when it reaches one.                                 */
/* -------------------------------------------------------------------------- */
int	mouse_move(int x, int y, t_data *data)
{
	static int	last[2] = {0, 0};

	if (data->proj && data->event.lock)
	{
		data->event.rp_y = (float)(last[0] - x) / 10;
		data->event.rp_x = (float)(y - last[1]) / 10;
		if (x <= 0)
			mlx_mouse_move(data->mlx, data->win, data->win_wid - 2, y);
		else if (x >= data->win_wid - 1)
			mlx_mouse_move(data->mlx, data->win, 1, y);
	}
	last[0] = x % data->win_wid;
	last[1] = y % data->win_len;
	return (1);
}
