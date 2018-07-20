/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgrigore <rgrigore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 21:47:02 by rgrigore          #+#    #+#             */
/*   Updated: 2017/12/28 18:33:57 by rgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H
# include <string.h>
# include <stdint.h>
# include <stdlib.h>

typedef struct	s_etris
{
	uint64_t			value;
	struct s_etris		*last;
	unsigned char		id;
	unsigned char		x;
	unsigned char		y;
	unsigned char		width;
	unsigned char		height;
}				t_etris;

void			ft_bzero(void *s, size_t n);
int				read_tetri(const int fd, t_etris *tetris);
int				solve(t_etris *tetris, const int count, uint16_t *map);
int				check_piece(const t_etris *tetris, uint16_t *map);
void			toggle_piece(const t_etris *tetris, uint16_t *map);
#endif
