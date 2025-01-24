/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:58:28 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/16 11:31:16 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/libft.h"
# include <math.h>
# include <mlx.h>
# include <fcntl.h>
# include <time.h>
// #include <stdio.h>

# define TARGET_FPS 60

typedef struct timespec	t_time;

typedef struct s_trigometry_values
{
	float	sin;
	float	cos;
}	t_trig;

typedef struct s_color
{
	int	re;
	int	gr;
	int	bl;
}	t_col;

typedef struct s_vector
{
	float	x;
	float	y;
	float	z;
}	t_vec;

typedef struct s_quat
{
	float	w;
	float	x;
	float	y;
	float	z;
}	t_quat;

typedef struct s_point
{
	int		x;
	int		y;
	int		z;
	t_col	col;
}	t_point;

typedef struct s_line
{
	t_point	start;
	t_point	end;
}	t_line;

typedef struct s_base
{
	t_vec	i;
	t_vec	j;
	t_vec	k;
}	t_base;

typedef struct s_matrix
{
	int	**matrix;
	int	**color;
	int	len;
	int	wid;
	int	col;
}	t_mat;

typedef struct s_object
{
	t_base	base;
	t_base	init;
	t_vec	mat_ori;
	t_point	wld_ori;
	t_vec	r_ori;
	t_vec	rot;
	t_mat	mat;
	int		scale;
	float	max_h;
	float	min_h;
}	t_obj;

typedef struct s_camera
{
	t_base	base;
	t_base	init;
	t_vec	ori;
	t_vec	r_ori;
	t_vec	rot;
	int		scale;
	int		n_plane;
}	t_cam;

typedef struct s_world
{
	t_base	base;
	t_base	init;
	t_cam	cam;
	int		init_scale;
}	t_wld;

typedef struct s_events
{
	int		mo_f;
	int		mo_s;
	int		mo_u;
	int		rot_x;
	int		rot_y;
	int		rot_z;
	int		lock;
	int		rot_fix;
	float	rp_x;
	float	rp_y;
	int		sc;
	int		inc;
	int		init;
}	t_event;

typedef struct s_modifiers
{
	int		ind;
	float	fog;
	float	mo_speed;
	float	rot_speed;
	float	fov;
	int		f_plane;
	float	height;
	int		r_move;
}	t_modif;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	void	*img;
	int		control;
	int		fps;
	int		proj;
	int		win_len;
	int		win_wid;
	float	d_time;
	t_event	event;
	t_modif	modif;
	t_obj	obj;
	t_wld	wld;
}	t_data;

/************************/
/*		main.c			*/
/************************/
t_data	*get_data(void);
void	loop(void);

/************************/
/*		fps.c			*/
/************************/
void	limit_frame_rate(const t_time *frame_start_time);
int		calculate_fps(t_data *data);

/************************/
/*		draw_persp.c	*/
/************************/
t_point	get_obj_coo(t_wld wld, t_obj obj);
void	draw_persp(t_data *data, int color);

/************************/
/*		status.c		*/
/************************/
void	clear_lines(int lines);
void	update_terminal_status(t_data *data, int init);

/************************/
/*		event.c			*/
/************************/
int		event_loop(t_data *data);

/************************/
/*		mlx.c			*/
/************************/
int		key_down(int keycode, t_data *data);
int		key_up(int keycode, t_data *data);
int		mouse_down(int button, int x, int y, t_data *data);
int		mouse_up(int button, int x, int y, t_data *data);
int		mouse_move(int x, int y, t_data *data);

/************************/
/*		mlx_utils.c		*/
/************************/
int		mlx_close(t_data *data);

/************************/
/*		movement.c		*/
/************************/
void	go_up(t_data *data, int sign);
void	move_forward(t_data *data, int sign);
void	move_side(t_data *data, int sign);

/************************/
/*		draw.c			*/
/************************/
void	draw_line(t_data *data, t_point start, t_point end);
int		create_line(t_data *data, t_point start, t_point end, int col);
void	draw_map(t_data *data, int color);

/************************/
/*		draw_utils.c	*/
/************************/
void	put_pixel(t_data *data, t_point point, int color);
int		point_is_in_fov(t_data *data, t_point point);
void	draw_low(t_data *data, t_point start, t_point end);
void	draw_high(t_data *data, t_point start, t_point end);

/************************/
/*		projection.c	*/
/************************/
int		calc_point(t_data *data, t_line *line, t_vec *start, t_vec *end);

/************************/
/*		projection_		*/
/*			utils.c		*/
/************************/
int		move_point(t_data *data, t_point *start, t_point *end);
void	change_point(t_vec *change, t_vec other, int z);
void	go_to_proj(t_data *data);

/************************/
/*		vec.c			*/
/************************/
t_vec	vec(t_obj obj, t_wld wld, t_point point);
void	orthonormalize_base(t_base *base);

/************************/
/*		color.c			*/
/************************/
t_col	get_real_color(t_obj obj, t_wld wld, t_vec curr);
t_col	get_grad(t_col start, t_col end, float percent);
void	set_color(t_obj *obj);
void	get_color(t_data *data, t_line *line, t_point start, t_point end);

/************************/
/*		color_utils.c	*/
/************************/
int		calc_color(t_col col);
t_col	rev_calc_color(int col);
void	chose_color(t_col *col1, t_col *col2, float *percent);

/************************/
/*		float.c			*/
/************************/
float	round_float(float value, int n);
void	round_vec(t_vec *vec);

/************************/
/*		rotate.c		*/
/************************/
void	look_at(t_base *base, t_base init, t_vec rot);
// void	rot_cam(t_vec cam_r, t_base *base, float sign, int axis);
void	do_rot(t_vec *cam_r, t_base *base, float sign, int axis);

/************************/
/*		rotate_utils.c	*/
/************************/
void	do_rot_yxz(t_vec *vec, t_trig rot_y, t_trig rot_x, t_trig rot_z);
void	do_rotx(t_base *base, t_trig vals);
void	do_roty(t_base *base, t_trig vals);
void	do_rotz(t_base *base, t_trig vals);
void	block_cam(float val, float *rot, int axis);
void	block_rot(float *val, float *rot, int axis);

/************************/
/*		rotate_         */
/*         quaternion.c	*/
/************************/
t_vec	rot_vec(t_vec v, t_quat q);
t_quat	eul_to_quat(float angle, t_vec axis);

/************************/
/*		init.c			*/
/************************/
void	new_window(t_data *data);
void	init_data(t_data *data, char **path);

/************************/
/*		parser.c		*/
/************************/
void	parse_file(t_obj *obj, char *path);

/************************/
/*		parser_utils.c	*/
/************************/
int		line_size(char **line);
// void	find_extrem(int val, t_obj *obj);
void	extract_data(t_obj	*obj, char *data, int x, int y);
int		is_valid_arg(char *str);
void	get_matsize(t_mat *mat, int fd);

/************************/
/*		end.c			*/
/************************/
int		mlx_del(t_data *data);
void	ft_perror(int error_code, int clean, char *custom_mess);
void	ft_pend_prog(void);

#endif