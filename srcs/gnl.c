/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkalia <hkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/19 16:43:21 by hkalia            #+#    #+#             */
/*   Updated: 2017/02/20 12:41:04 by hkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

static int	final_line(char **line, t_arr *str)
{
	GRD1((*line = ft_memalloc(str->len + 1)) == 0, arr_dtr(str), -1);
	ft_memcpy(*line, str->ptr, str->len);
	str->len = 0;
	return (1);
}

static int	assign_line(char **line, t_arr *str, size_t src_len)
{
	GRD1((*line = ft_memalloc(src_len + 1)) == 0, arr_dtr(str), -1);
	ft_memcpy(*line, str->ptr, src_len);
	arr_removem(str, 0, src_len + 1);
	return (1);
}

int			gnl(const int fd, char **line)
{
	static t_arr	str = {0, {0, 0, 0, 0}, 0, 0};
	char			buf[BUFF_SIZE];
	uint8_t			*tmp;
	ssize_t			r;

	if (fd < 0 || line == 0 || BUFF_SIZE == 0)
		return (-1);
	if (str.cap == 0)
		GRD(arr_init(&str, BUFF_SIZE, (t_arr_elm){sizeof(char), 0, 0, 0}) == -1
			, -1);
	while ((r = read(fd, buf, BUFF_SIZE)) != 0)
	{
		GRD1(r == -1, arr_dtr(&str), -1);
		GRD1(arr_appendm(&str, buf, r) == -1, arr_dtr(&str), -1);
		if ((tmp = ft_memchr(str.ptr, '\n', str.len)) != 0)
			return (assign_line(line, &str, tmp - str.ptr));
	}
	if ((tmp = ft_memchr(str.ptr, '\n', str.len)) != 0)
		return (assign_line(line, &str, tmp - str.ptr));
	else if (str.len > 0)
		return (final_line(line, &str));
	arr_dtr(&str);
	return (0);
}
