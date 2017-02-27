/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkalia <hkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 15:16:04 by hkalia            #+#    #+#             */
/*   Updated: 2017/02/26 18:42:41 by hkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

static void		mat_rotx(float dst[4][4], float src)
{
	dst[0][0] = 1;
	dst[1][1] = cos(src);
	dst[1][2] = sin(src);
	dst[2][1] = -sin(src);
	dst[2][2] = cos(src);
	dst[3][3] = 1;
}

static void		mat_roty(float dst[4][4], float src)
{
	dst[0][0] = cos(src);
	dst[0][2] = -sin(src);
	dst[1][1] = 1;
	dst[2][0] = sin(src);
	dst[2][2] = cos(src);
	dst[3][3] = 1;
}

static void		mat_rotz(float dst[4][4], float src)
{
	dst[0][0] = cos(src);
	dst[0][1] = sin(src);
	dst[1][0] = -sin(src);
	dst[1][1] = cos(src);
	dst[2][2] = 1;
	dst[3][3] = 1;
}

void			mat_rotate(float dst[4][4], t_fxyz src)
{
	float matx[4][4];
	float maty[4][4];
	float matz[4][4];
	float tmp1[4][4];
	float tmp2[4][4];

	ft_bzero(matx, sizeof(float [4][4]));
	ft_bzero(maty, sizeof(float [4][4]));
	ft_bzero(matz, sizeof(float [4][4]));
	mat_rotx(matx, src.x);
	mat_roty(maty, src.y);
	mat_rotz(matz, src.z);
	mat_mult(tmp1, dst, maty);
	mat_mult(tmp2, tmp1, matx);
	mat_mult(dst, tmp2, matz);
}

void			vec_mat_mult(t_fxyz *dst, t_fxyz *src1, float src2[4][4])
{
	dst->x = src1->x * src2[0][0]
			+ src1->y * src2[1][0]
			+ src1->z * src2[2][0] + src2[3][0];
	dst->y = src1->x * src2[0][1]
			+ src1->y * src2[1][1]
			+ src1->z * src2[2][1] + src2[3][1];
	dst->z = src1->x * src2[0][2]
			+ src1->y * src2[1][2]
			+ src1->z * src2[2][2] + src2[3][2];
}
