/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkalia <hkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 16:49:38 by hkalia            #+#    #+#             */
/*   Updated: 2017/02/21 20:26:39 by hkalia           ###   ########.fr       */
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

static void	gfx_imgcpy(t_img dst, t_img src)
{
	size_t	sze;
	size_t	i;

	sze = dst.max.x * dst.max.y;
	i = 0;
	while (i < sze)
	{
		if (src.img[i] != 0)
			dst.img[i] = src.img[i];
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
	mlx_put_image_to_window(mlx->id, mlx->win.id, mlx->img.id, 0, 0);
	mlx->mouse.flg = 0;
	mlx->mouse.r.btn = button;
	mlx->mouse.r.pos.x = x;
	mlx->mouse.r.pos.y = y;
	return (0);
}

static void	gfx_imgmerge(t_img dst, t_img src1, t_img src2)
{
	size_t	sze;
	size_t	i;

	sze = dst.max.x * dst.max.y;
	i = 0;
	while (i < sze)
	{
		if (src1.img[i] != 0)
			dst.img[i] = src1.img[i];
		else if (src2.img[i] != 0)
			dst.img[i] = src2.img[i];
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
