/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkalia <hkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 15:38:12 by hkalia            #+#    #+#             */
/*   Updated: 2016/12/12 11:58:09 by hkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <str.h>
#include <ft_stdio.h>
#include <unistd.h>

void	ft_putendl(const char *src)
{
	while (*src)
	{
		write(1, src, 1);
		src++;
	}
	write(1, "\n", 1);
}
