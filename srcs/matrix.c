/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkalia <hkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 15:16:04 by hkalia            #+#    #+#             */
/*   Updated: 2017/02/25 21:36:25 by hkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	mat_mult(float dst[4][4], float src1[4][4], float src2[4][4])
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			dst[i][j] = src1[i][0] * src2[0][j] + src1[i][1] * src2[1][j]
						+ src1[i][2] * src2[2][j] + src1[i][3] * src2[3][j];
			++j;
		}
		++i;
	}
}

void	mat_id(float src[4][4])
{
	ft_bzero(src, sizeof(float [4][4]));
	src[0][0] = 1;
	src[1][1] = 1;
	src[2][2] = 1;
	src[3][3] = 1;
}

void	mat_translate(float dst[4][4], t_fxyz src)
{
	float	tmp[4][4];

	mat_id(tmp);
	tmp[3][0] = src.x;
	tmp[3][1] = src.y;
	tmp[3][2] = src.z;
	mat_mult(dst, dst, tmp);
}

void	mat_scale(float dst[4][4], t_fxyz src)
{
	float	tmp[4][4];

	ft_bzero(tmp, sizeof(float [4][4]));
	tmp[0][0] = src.x;
	tmp[1][1] = src.y;
	tmp[2][2] = src.z;
	tmp[3][3] = 1;
	mat_mult(dst, dst, tmp);
}
