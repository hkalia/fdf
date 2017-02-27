/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkalia <hkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 17:08:34 by hkalia            #+#    #+#             */
/*   Updated: 2017/02/25 21:41:20 by hkalia           ###   ########.fr       */
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
	t_fxyz		*local;
	t_fxyz		*world;
	t_fxyz		*aligned;
	t_fxyz		*projected;
	int			color;
}				t_vertex;


typedef struct	s_click
{
	int			btn;
	t_ixy		pos;
}				t_click;

typedef struct	s_mouse
{
	bool		flg;
	t_click		p;
	t_click		r;
	t_ixy		pos;
}				t_mouse;

typedef struct	s_img
{
	void		*id;
	int			*img;
	int			ln;
	t_ixy		max;
}				t_img;

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
	t_img		cur;
	t_img		img;
	t_mouse		mouse;
}				t_mlx;

int				gnl(const int fd, char **line);
t_img			gfx_imgnew(void *mlx_id, t_ixy sze);
void			pixel(t_img img, int color, t_ixy src);
void			line(t_img img, int color, t_ixyxy src);
void			square(t_img img, int color, t_ixyxy src);
int				key_press(int keycode, void *param);
int				key_release(int keycode, void *param);
int				mouse_press(int button, int x, int y, void *param);
int				mouse_release(int button, int x, int y, void *param);
int				mouse_motion(int x, int y, void *param);

#endif
