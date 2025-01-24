/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 10:30:03 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/16 10:39:33 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* -------------------------------------------------------------------------- */
/* Function used to parse a line. If at any point, an argument is invalid, we */
/* return 1 significating that everything must be stopped.                    */
/* -------------------------------------------------------------------------- */
int	parse_line(t_obj *obj, char *src, int line)
{
	int		j;
	int		i;
	int		test;

	obj->mat.matrix[line] = ft_calloc(obj->mat.wid + 1, sizeof(int));
	obj->mat.color[line] = ft_calloc(obj->mat.wid + 1, sizeof(int));
	if (!obj->mat.matrix[line] || !obj->mat.color[line] || !src)
		return (1);
	j = 0;
	i = -1;
	while (src[++i])
	{
		test = is_valid_arg(src + i);
		if (j == obj->mat.wid || test == -1)
			return (1);
		extract_data(obj, src + i, j, line);
		j++;
		i += test;
	}
	if (j != obj->mat.wid)
		return (1);
	return (0);
}

/* -------------------------------------------------------------------------- */
/* Function used to initialise the matrix of the obj. To do so, we first      */
/* retrieve the width and len of the map. We then read the while file once    */
/* again, and call parse line on each line.                                   */
/* -------------------------------------------------------------------------- */
void	parse_file(t_obj *obj, char *path)
{
	char	*line;
	int		fd;
	int		i;

	obj->mat = (t_mat){NULL, NULL, 0, 0, 0};
	get_matsize(&obj->mat, open(path, O_RDONLY));
	if (obj->mat.len == 0 || obj->mat.wid == 0)
		ft_perror(0, 0, "The map is empty.");
	obj->mat.matrix = ft_calloc(obj->mat.len + 1, sizeof(int *));
	obj->mat.color = ft_calloc(obj->mat.len + 1, sizeof(int *));
	fd = open(path, O_RDONLY);
	if (fd == -1 || !obj->mat.matrix || !obj->mat.color)
		ft_perror(3, mlx_del(NULL), NULL);
	i = -1;
	while (++i < obj->mat.len)
	{
		line = get_next_line(fd);
		if (parse_line(obj, line, i))
			ft_perror(4, mlx_del(NULL), NULL);
		ft_del(line);
	}
	close(fd);
}
