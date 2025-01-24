/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@students.42perpignan    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:35:04 by hle-hena          #+#    #+#             */
/*   Updated: 2024/11/18 18:06:08 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strtrim(const char *s1, const char *set)
{
	int		start;
	int		len;

	len = ft_strlen(s1) - 1;
	start = 0;
	while (start <= len && ft_strchr(set, s1[start]))
		start ++;
	while (len >= 0 && ft_strchr(set, s1[len]))
		len --;
	if (start <= len)
		return (ft_substr(s1, start, len - start + 1));
	return (ft_calloc(1, sizeof(char)));
}
