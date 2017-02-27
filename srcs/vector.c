/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkalia <hkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 15:16:04 by hkalia            #+#    #+#             */
/*   Updated: 2017/02/25 21:18:08 by hkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

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
