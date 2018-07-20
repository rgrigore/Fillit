/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgrigore <rgrigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 21:26:11 by rgrigore          #+#    #+#             */
/*   Updated: 2017/12/28 18:33:11 by rgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdio.h>

int			solve_map(t_etris *tet, const int size, uint16_t *map)
{
	int pos;

	if (tet->id == 0)
		return (1);
	pos = (tet->last ? (tet->last->x + tet->last->y * size) : 0);
	tet->y = pos / size - 1;
	while (++tet->y <= size - tet->height)
	{
		tet->x = (tet->y == pos / size ? pos % size - 1 : -1);
		while (++tet->x <= size - tet->width)
			if (!(*(uint64_t *)(map + tet->y) & (tet->value >> tet->x)))
			{
				*(uint64_t *)(map + tet->y) |= (tet->value >> tet->x);
				if (solve_map(tet + 1, size, map))
					return (1);
				*(uint64_t *)(map + tet->y) ^= (tet->value >> tet->x);
			}
	}
	tet->x = 0;
	tet->y = 0;
	return (0);
}

int			solve(t_etris *tet, const int count, uint16_t *map)
{
	int		size;

	size = 2;
	while (size * size < count * 4)
		size++;
	while (!solve_map(tet, size, map) && size <= 16)
	{
		ft_bzero(map, sizeof(uint16_t) * 16);
		size++;
	}
	return (size == 17 ? 0 : size);
}
