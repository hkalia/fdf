/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkalia <hkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 16:49:38 by hkalia            #+#    #+#             */
/*   Updated: 2017/02/21 18:55:14 by hkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

int		mouse_press(int button, int x, int y, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	GRD(x >= mlx->win.max.x || y >= mlx->win.max.y || x < 0 || y < 0, 0);
	printf("\e[34mMouse Press: Button:%d X:%d Y:%d\e[0m\n", button, x, y);
	mlx->mouse.flg = 1;
	mlx->mouse.p.btn = button;
	mlx->mouse.p.pos.x = x;
	mlx->mouse.p.pos.y = y;
	return (0);
}

static void	gfx_imgcpy(t_img _dst, t_img _src)
{
	int		*dst;
	int		*src;
	size_t	sze;
	size_t	i;

	dst = (int *)_dst.img;
	src = (int *)_src.img;
	sze = _dst.max.x * _dst.max.y;
	i = 0;
	while (i < sze)
	{
		if (src[i] != 0)
			dst[i] = src[i];
		++i;
	}
}

int		mouse_release(int button, int x, int y, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	GRD(x >= mlx->win.max.x || y >= mlx->win.max.y || x < 0 || y < 0, 0);
	printf("\e[34mMouse Release: Button:%d X:%d Y:%d\e[0m\n", button, x, y);
	gfx_imgcpy(mlx->img, mlx->cur);
	ft_bzero(mlx->cur.img, mlx->cur.max.x * mlx->cur.max.y * 4);
	mlx_put_image_to_window(mlx->id, mlx->win.id, mlx->img.id, 0, 0);
	mlx->mouse.flg = 0;
	mlx->mouse.r.btn = button;
	mlx->mouse.r.pos.x = x;
	mlx->mouse.r.pos.y = y;
	return (0);
}

static void	gfx_imgmerge(t_img _dst, t_img _src1, t_img _src2)
{
	int		*dst;
	int		*src1;
	int		*src2;
	size_t	sze;
	size_t	i;

	dst = (int *)_dst.img;
	src1 = (int *)_src1.img;
	src2 = (int *)_src2.img;
	sze = _dst.max.x * _dst.max.y;
	i = 0;
	while (i < sze)
	{
		if (src1[i] != 0)
			dst[i] = src1[i];
		else if (src2[i] != 0)
			dst[i] = src2[i];
		++i;
	}
}

int		mouse_motion(int x, int y, void *param)
{
	t_mlx	*mlx;
	t_img	tmp;

	mlx = (t_mlx *)param;
	GRD(x >= mlx->win.max.x || y >= mlx->win.max.y || x < 0 || y < 0, 0);
	printf("\e[34mMouse Motion: X:%d Y:%d\e[0m\n", x, y);
	mlx->mouse.pos.x = x;
	mlx->mouse.pos.y = y;
	GRD(mlx->mouse.flg == 0, 0);
	tmp = gfx_imgnew(mlx->id, (t_ixy){mlx->win.max.x, mlx->win.max.y});
	GRD1(tmp.id == 0, perror("\e[31mERROR: gfx_imgnew\e[0m\n"), -1);
	ft_bzero(mlx->cur.img, mlx->cur.max.x * mlx->cur.max.y * 4);
	square(mlx->cur, 0x00FF0000, (t_ixyxy){mlx->mouse.p.pos.x
			, mlx->mouse.p.pos.y, x, y});
	gfx_imgmerge(tmp, mlx->img, mlx->cur);
	mlx_put_image_to_window(mlx->id, mlx->win.id, tmp.id, 0, 0);
	mlx_destroy_image(mlx->id, tmp.id);
	return (0);
}
