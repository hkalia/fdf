/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkalia <hkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 17:05:38 by hkalia            #+#    #+#             */
/*   Updated: 2017/02/26 20:23:14 by hkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
/*
** #define KEY_A 0
** #define KEY_S 1
** #define KEY_D 2
** #define KEY_F 3
** #define KEY_Q 12
** #define KEY_W 13
** #define KEY_E 14
** #define KEY_R 15
** #define KEY_PLUS 69
** #define KEY_MINUS 78
** #define KEY_UP 126
** #define KEY_DOWN 125
** #define KEY_LEFT 123
** #define KEY_RIGHT 124
*/

int		key_press_hook(int keycode, t_mlx *mlx)
{
	GRD3(keycode == 53, mlx_destroy_image(mlx->id, mlx->img.id)
		, mlx_destroy_window(mlx->id, mlx->win.id), exit(0), 0);
	if (keycode == 0)
		mlx->scene.world.y -= 0.05;
	if (keycode == 1)
		mlx->scene.world.x -= 0.05;
	if (keycode == 2)
		mlx->scene.world.y += 0.05;
	if (keycode == 3)
		--mlx->scene.focal_dist;
	if (keycode == 12)
		mlx->scene.world.z += 0.05;
	if (keycode == 13)
		mlx->scene.world.x += 0.05;
	if (keycode == 14)
		mlx->scene.world.z -= 0.05;
	if (keycode == 15)
		--mlx->scene.focal_dist;
	if (keycode == 69)
		;
	if (keycode == 78)
		;
	if (keycode == 126)
		;
	if (keycode == 125)
		;
	if (keycode == 123)
		;
	if (keycode == 124)
		;
	return (0);
}

int		exit_hook(t_mlx *mlx)
{
	mlx_destroy_image(mlx->id, mlx->img.id);
	mlx_destroy_window(mlx->id, mlx->win.id);
	exit(0);
}
