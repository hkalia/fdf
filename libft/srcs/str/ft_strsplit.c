/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkalia <hkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 15:40:20 by hkalia            #+#    #+#             */
/*   Updated: 2016/12/12 11:14:28 by hkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <str.h>
#include <tbl.h>
#include <stdlib.h>

static size_t	ft_nbr_wrd_in_str(const char *src, char src_x)
{
	size_t	nbr_wrd;
	int		flwrd;

	nbr_wrd = 0;
	flwrd = 0;
	while (*src)
	{
		if (*src == src_x && flwrd == 1)
			flwrd = 0;
		if (*src != src_x && flwrd == 0)
		{
			flwrd = 1;
			nbr_wrd++;
		}
		src++;
	}
	return (nbr_wrd);
}

static char		*ft_wrddup(const char *src, char src_x)
{
	char	*wrd;
	size_t	wrd_len;
	size_t	i;

	wrd_len = 0;
	i = 0;
	while (src[wrd_len] && src[wrd_len] != src_x)
		wrd_len++;
	if (!(wrd = ft_strnew(wrd_len)))
		return (NULL);
	while (i < wrd_len)
	{
		wrd[i] = src[i];
		i++;
	}
	return (wrd);
}

char			**ft_strsplit(const char *src, char src_x)
{
	char	**table;
	size_t	nbr_wrd;
	size_t	i;
	int		flwrd;

	if (src == 0)
		return (0);
	i = 0;
	flwrd = 0;
	nbr_wrd = ft_nbr_wrd_in_str(src, src_x);
	if (!(table = ft_tblnew(nbr_wrd)))
		return (NULL);
	while (*src && i < nbr_wrd)
	{
		if (*src == src_x && flwrd == 1)
			flwrd = 0;
		if (*src != src_x && flwrd == 0)
		{
			flwrd = 1;
			GRD1(!(table[i] = ft_wrddup(src, src_x)), ft_tbldel(table), 0);
			++i;
		}
		src++;
	}
	return (table);
}
