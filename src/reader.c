/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgrigore <rgrigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 21:25:59 by rgrigore          #+#    #+#             */
/*   Updated: 2017/12/28 18:33:02 by rgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "fillit.h"

void	min_max(const char *str, char *m)
{
	unsigned char i;

	i = 0;
	m[0] = 3;
	m[1] = 0;
	m[2] = 3;
	m[3] = 0;
	while (i < 20)
	{
		if (str[i] == '#')
		{
			if (i % 5 < m[0])
				m[0] = i % 5;
			if (i % 5 > m[1])
				m[1] = i % 5;
			if (i / 5 < m[2])
				m[2] = i / 5;
			if (i / 5 > m[3])
				m[3] = i / 5;
		}
		i++;
	}
}

t_etris	get_piece(const char *str, const char id)
{
	t_etris	tetris;
	char	m[4];
	int		i;
	int		j;

	min_max(str, m);
	tetris.width = m[1] - m[0] + 1;
	tetris.height = m[3] - m[2] + 1;
	tetris.id = id;
	tetris.value = 0;
	tetris.last = NULL;
	i = -1;
	while (++i < tetris.height)
	{
		j = -1;
		while (++j < tetris.width)
			if (str[(m[0] + j) + (m[2] + i) * 5] == '#')
				tetris.value |= (1L << (16 * (i + 1) - 1 - j));
	}
	return (tetris);
}

int		check_connection(const char *str)
{
	int block;
	int i;

	block = 0;
	i = 0;
	while (i < 20)
	{
		if (str[i] == '#')
		{
			if ((i + 1) < 20 && str[i + 1] == '#')
				block++;
			if ((i - 1) >= 0 && str[i - 1] == '#')
				block++;
			if ((i + 5) < 20 && str[i + 5] == '#')
				block++;
			if ((i - 5) >= 0 && str[i - 5] == '#')
				block++;
		}
		i++;
	}
	return (block == 6 || block == 8);
}

int		check_counts(const char *str, const int count)
{
	int i;
	int blocks;

	blocks = 0;
	i = 0;
	while (i < 20)
	{
		if (i % 5 < 4)
		{
			if (!(str[i] == '#' || str[i] == '.'))
				return (1);
			if (str[i] == '#' && ++blocks > 4)
				return (2);
		}
		else if (str[i] != '\n')
			return (3);
		i++;
	}
	if (count == 21 && str[20] != '\n')
		return (4);
	if (!check_connection(str))
		return (5);
	return (0);
}

int		read_tetri(const int fd, t_etris *tetris)
{
	char	buf[22];
	int		count;
	int		i;
	int		j;
	char	cur;

	cur = 'A';
	i = 0;
	while ((count = read(fd, buf, 21)) >= 20)
	{
		if (check_counts(buf, count) != 0)
			return (0);
		tetris[i] = get_piece(buf, cur++);
		j = i;
		while (--j >= 0)
			if (tetris[j].value == tetris[i].value)
				tetris[i].last = tetris + j;
		i++;
		j = count;
	}
	if (count != 0 || j != 20)
		return (0);
	return (cur - 'A');
}
