/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkalia <hkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 17:08:34 by hkalia            #+#    #+#             */
/*   Updated: 2017/04/16 16:09:56 by hkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define BUFF_SIZE 100
# define WIN_X 640
# define WIN_Y 480

# include <libarr.h>
# include <libft.h>
# include <mlx.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <stdbool.h>
# include <stdint.h>

typedef struct	s_sxy
{
	short		x;
	short		y;
}				t_sxy;

typedef struct	s_ixy
{
	int			x;
	int			y;
}				t_ixy;

typedef struct	s_ixyz
{
	int			x;
	int			y;
	int			z;
}				t_ixyz;

typedef struct	s_ixyxy
{
	int			x0;
	int			y0;
	int			x1;
	int			y1;
}				t_ixyxy;

typedef struct	s_fxy
{
	float		x;
	float		y;
}				t_fxy;

typedef struct	s_fxyz
{
	float		x;
	float		y;
	float		z;
}				t_fxyz;

typedef struct	s_vertex
{
	t_fxyz		local;
	t_fxyz		world;
	t_fxyz		aligned;
	t_fxyz		projected;
}				t_vertex;

typedef struct	s_img
{
	void		*id;
	int			*img;
	int			ln;
	t_ixy		max;
}				t_img;

typedef struct	s_scene
{
	t_vertex	**points;
	t_fxyz		world;
	float		scale;
	t_fxyz		scales;
	t_fxyz		trans;
	short		focal_dist;
}				t_scene;

typedef struct	s_win
{
	void		*id;
	t_ixy		max;
}				t_win;

typedef struct	s_mlx
{
	void		*id;
	t_arr		src;
	t_win		win;
	t_scene		scene;
	t_img		img;
}				t_mlx;

t_img			imgnew(void *mlx_id, t_ixy sze);
void			pixel(t_img img, int color, t_ixy src);
void			line(t_img img, int color, t_ixyxy src);
void			square(t_img img, int color, t_ixyxy src);
int				key_press_hook(int keycode, t_mlx *mlx);
int				exit_hook(t_mlx *mlx);
void			mat_mult(float dst[4][4], float src1[4][4], float src2[4][4]);
void			mat_id(float src[4][4]);
void			mat_translate(float dst[4][4], t_fxyz src);
void			mat_scale(float dst[4][4], t_fxyz src);
void			mat_rotate(float dst[4][4], t_fxyz src);
void			vec_mat_mult(t_fxyz *dst, t_fxyz *src1, float src2[4][4]);

#endif
