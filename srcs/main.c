/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkalia <hkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 15:16:04 by hkalia            #+#    #+#             */
/*   Updated: 2017/02/21 18:36:17 by hkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

t_img	gfx_imgnew(void *mlx_id, t_ixy sze)
{
	t_img	ret;

	ret = (t_img){0, 0, 0, 0, 0, {0, 0}};
	if ((ret.id = mlx_new_image(mlx_id, sze.x, sze.y)) == 0)
	{
		perror("\e[31mERROR: mlx_new_image\e[0m\n");
		return (ret);
	}
	ret.img = mlx_get_data_addr(ret.id, &ret.bpp, &ret.ln, &ret.end);
	ret.bpp /= 8;
	ret.max = sze;
	return (ret);
}

static int8_t	mlx_start(t_mlx *mlx)
{
	GRD1(!(mlx->id = mlx_init()), perror("\e[31mERROR: mlx_init\e[0m\n"), -1);
	mlx->win.max.x = 640;
	mlx->win.max.y = 480;
	GRD1(!(mlx->win.id = mlx_new_window(mlx->id, mlx->win.max.x, mlx->win.max.y
		, "42")), perror("\e[31mERROR: mlx_new_window\e[0m\n"), -1);
	mlx->img = gfx_imgnew(mlx->id, (t_ixy){mlx->win.max.x, mlx->win.max.y});
	GRD1(mlx->img.id == 0, perror("\e[31mERROR: gfx_imgnew\e[0m\n"), -1);
	mlx->cur = gfx_imgnew(mlx->id, (t_ixy){mlx->win.max.x, mlx->win.max.y});
	GRD1(mlx->cur.id == 0, perror("\e[31mERROR: gfx_imgnew\e[0m\n"), -1);
	return (0);
}

static int8_t	reader(char *filename, t_mlx *mlx)
{
	int		fd;
	int		r;
	char	*line;

	GRD1((fd = open(filename, O_RDONLY)) == -1
		, perror("\e[31mERROR: open\e[0m\n"), -1);
	GRD1(arr_init(&mlx->src, 100, (t_arr_elm){sizeof(char), 0, 0, 0}) == -1
		, perror("\e[31mERROR: arr_init\e[0m\n"), -1);
	while ((r = gnl(fd, &line)) == 1)
	{
		GRD1(arr_appendm(&mlx->src, line, ft_strlen(line)) == -1
			, perror("\e[31mERROR: arr_insertat\e[0m\n"), -1);
		free(line);
	}
	GRD1(r == -1, perror("\e[31mERROR: gnl\e[0m\n"), -1);
	close(fd);
	return (0);
}

int				main(int ac, char **av)
{
	t_mlx	mlx;

	GRD1(ac != 2, printf("Usage : %s <filename> [ case_size z_size ]", av[0])
		, -1);
	ft_bzero(&mlx, sizeof(mlx));
	GRD1(reader(av[1], &mlx) == -1, perror("\e[31mERROR: reader\e[0m\n"), -1);
	GRD(mlx_start(&mlx) == -1, -1);
	mlx_hook(mlx.win.id, 2, 0, key_press, &mlx);
	mlx_hook(mlx.win.id, 3, 0, key_release, &mlx);
	mlx_hook(mlx.win.id, 4, 0, mouse_press, &mlx);
	mlx_hook(mlx.win.id, 5, 0, mouse_release, &mlx);
	mlx_hook(mlx.win.id, 6, 0, mouse_motion, &mlx);
	mlx_loop(mlx.id);
	return (0);
}
