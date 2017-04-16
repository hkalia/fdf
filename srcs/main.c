/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkalia <hkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 15:16:04 by hkalia            #+#    #+#             */
/*   Updated: 2017/04/16 16:12:42 by hkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

t_img			imgnew(void *mlx_id, t_ixy sze)
{
	t_img	ret;
	int		tmp;
	int		tmp1;

	ret = (t_img){0, 0, 0, {0, 0}};
	GRD1((ret.id = mlx_new_image(mlx_id, sze.x, sze.y)) == 0
		, perror("\e[31mERROR: mlx_new_image\e[0m"), ret);
	ret.img = (int *)mlx_get_data_addr(ret.id, &tmp, &ret.ln, &tmp1);
	ret.ln /= 4;
	ret.max = sze;
	return (ret);
}

static int8_t	mlx_start(t_mlx *mlx)
{
	GRD1(!(mlx->id = mlx_init()), perror("\e[31mERROR: mlx_init\e[0m"), -1);
	mlx->win.max.x = WIN_X;
	mlx->win.max.y = WIN_Y;
	GRD1(!(mlx->win.id = mlx_new_window(mlx->id, mlx->win.max.x, mlx->win.max.y
		, "42")), perror("\e[31mERROR: mlx_new_window\e[0m"), -1);
	mlx->img = imgnew(mlx->id, (t_ixy){mlx->win.max.x, mlx->win.max.y});
	GRD1(mlx->img.id == 0, perror("\e[31mERROR: imgnew\e[0m"), -1);
	return (0);
}

static int8_t	reader(char *filename, t_mlx *mlx)
{
	int		fd;
	int		r;
	char	buf[BUFF_SIZE];

	GRD1(BUFF_SIZE == 0, perror("\e[31mERROR: BUFF_SIZE\e[0m"), -1);
	GRD1((fd = open(filename, O_RDONLY)) < 0, perror("\e[31mERROR: open\e[0m")
		, -1);
	GRD1(arr_init(&mlx->src, BUFF_SIZE, (t_arr_elm){sizeof(char), 0, 0
		, 0}) == -1, perror("\e[31mERROR: arr_init\e[0m"), -1);
	while ((r = read(fd, buf, BUFF_SIZE)) != 0)
	{
		GRD2(r == -1, arr_dtr(&mlx->src), perror("\e[31mERROR: read\e[0m")
			, -1);
		GRD2(arr_appendm(&mlx->src, buf, r) == -1, arr_dtr(&mlx->src)
			, perror("\e[31mERROR: arr_appendm\e[0m"), -1);
	}
	close(fd);
	return (0);
}

int				main(int ac, char **av)
{
	t_mlx	mlx;

	GRD1(ac != 2, printf("Usage : %s <filename> [ case_size z_size ]", av[0])
		, -1);
	ft_bzero(&mlx, sizeof(mlx));
	GRD1(reader(av[1], &mlx) == -1, perror("\e[31mERROR: reader\e[0m"), -1);
	printf("%s\n", arr_tostr(&mlx.src));
	GRD(mlx_start(&mlx) == -1, -1);
	mlx_hook(mlx.win.id, 2, 0, key_press_hook, &mlx);
	mlx_hook(mlx.win.id, 17, 0, exit_hook, &mlx);
	mlx_loop(mlx.id);
	return (0);
}
