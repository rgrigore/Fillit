/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgrigore <rgrigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 21:25:40 by rgrigore          #+#    #+#             */
/*   Updated: 2018/01/03 18:46:29 by rgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "fillit.h"

char	*empty_map(int size)
{
	char	*str;
	int		i;
	int		j;

	str = (char*)malloc(((size + 1) * size) * sizeof(char));
	ft_bzero(str, (size + 1) * size + 1);
	j = -1;
	while (++j < size)
	{
		i = -1;
		while (++i < size)
			str[j * (size + 1) + i] = '.';
		str[j * (size + 1) + i] = '\n';
	}
	return (str);
}

void	print(t_etris *tet, int count, int size)
{
	char	*str;
	int		i;
	int		j;

	str = empty_map(size);
	while (count-- > 0)
	{
		j = -1;
		while (++j < tet->height)
		{
			i = -1;
			while (++i < tet->width)
				if ((tet->value >> (16 * (j + 1) - 1 - i)) & 1)
					str[(tet->y + j) * (size + 1) + i + tet->x] = tet->id;
		}
		tet++;
	}
	while (*str)
		write(1, &(*str++), 1);
}

int		error(char *str)
{
	while (*str)
	{
		write(1, &(*str), 1);
		str++;
	}
	write(1, "\n", 1);
	return (1);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*c;
	size_t			i;

	c = (unsigned char*)s;
	i = 0;
	while (i < n)
		c[i++] = 0;
	s = c;
}

int		main(int argc, char **argv)
{
	t_etris		tetris[27];
	uint16_t	map[16];
	int			count;
	int			size;

	if (argc != 2)
		return (error("usage: ./fillit [input_file]"));
	ft_bzero(tetris, sizeof(t_etris) * (26 + 1));
	if (!(count = read_tetri(open(argv[1], O_RDONLY), tetris)))
		return (error("error"));
	ft_bzero(map, sizeof(uint16_t) * 16);
	if ((size = solve(tetris, count, map)) == 0)
		return (error("error"));
	print(tetris, count, size);
	return (0);
}
