/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkalia <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 15:39:23 by hkalia            #+#    #+#             */
/*   Updated: 2016/09/27 13:34:58 by hkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <str.h>

void	ft_strclr(char *src)
{
	if (src != 0)
		while (*src)
			*src++ = '\0';
}