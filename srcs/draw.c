/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkalia <hkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 15:16:04 by hkalia            #+#    #+#             */
/*   Updated: 2017/02/21 18:25:01 by hkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

static uint32_t	endian_change(uint32_t value)
{
	uint32_t	result = 0;

	result |= (value & 0x000000FF) << 24;
	result |= (value & 0x0000FF00) << 8;
	result |= (value & 0x00FF0000) >> 8;
	result |= (value & 0xFF000000) >> 24;
	return (result);
}

void			pixel(t_img img, int color, t_ixy src)
{
	int	*i;

	if (src.x >= img.max.x || src.y >= img.max.y || src.x < 0 || src.y < 0)
		return ;
	i = (int *)&img.img[src.x * img.bpp + src.y * img.ln];
	*i = img.end ? endian_change(color) : color;
}

void		line(t_img img, int color, t_ixyxy src)
{
	t_ixy	d;
	t_ixy	s;
	int		e1;
	int		e2;

	d.x = abs(src.x1 - src.x0);
	d.y = abs(src.y1 - src.y0);
	s.x = src.x0 < src.x1 ? 1 : -1;
	s.y = src.y0 < src.y1 ? 1 : -1;
	e1 = (d.x > d.y ? d.x : -d.y) / 2;
	while (!(src.x0 == src.x1 && src.y0 == src.y1))
	{
		pixel(img, color, (t_ixy){src.x0, src.y0});
		e2 = e1;
		if (e2 > -d.x)
		{
			e1 -= d.y;
			src.x0 += s.x;
		}
		if (e2 < d.y)
		{
			e1 += d.x;
			src.y0 += s.y;
		}
	}
}

void			square(t_img img, int color, t_ixyxy src)
{
	line(img, color, (t_ixyxy){src.x0, src.y0, src.x1, src.y0});
	line(img, color, (t_ixyxy){src.x1, src.y0, src.x1, src.y1});
	line(img, color, (t_ixyxy){src.x1, src.y1, src.x0, src.y1});
	line(img, color, (t_ixyxy){src.x0, src.y1, src.x0, src.y0});
}
