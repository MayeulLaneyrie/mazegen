/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findpath.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaneyri <mlaneyri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 20:42:29 by mlaneyri          #+#    #+#             */
/*   Updated: 2023/07/07 01:28:21 by lnr              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mazegen.h"

void priority(t_maze * mz, int xA, int xB, int prio[4]) {
	int deltaX = xB % mz->w - xA % mz->w;
	int deltaY = xB / mz->w - xA / mz->w;

	if (deltaX * deltaX > deltaY * deltaY) {
		prio[0] = (deltaX > 0 ? MV_E : MV_W);
		prio[1] = (deltaY > 0 ? MV_S : MV_N);
		prio[2] = (deltaY > 0 ? MV_N : MV_S);
		prio[3] = (deltaX > 0 ? MV_W : MV_E);
	}
	else {
		prio[0] = (deltaY > 0 ? MV_S : MV_N);
		prio[1] = (deltaX > 0 ? MV_E : MV_W);
		prio[2] = (deltaX > 0 ? MV_W : MV_E);
		prio[3] = (deltaY > 0 ? MV_N : MV_S);
	}
}

int find_path(t_maze * mz, int xA, int xB, int color) {
	int prio[4];

	mz->grid[xA] |= color << 4;
	maze_display(mz);
	usleep(10000);
	if (xA == xB) 
		return (1);
	priority(mz, xA, xB, prio);
	for (int i = 0; i <= 4; ++i) {
		if (move_possible(mz, xA, prio[i])
				&& ((mz->grid[move_box(mz, xA, prio[i])] & 0xfa) >> 4) != color)
			if (find_path(mz, move_box(mz, xA, prio[i]), xB, color))
				return (1);
	}
	mz->grid[xA] &= 0x0f;
	maze_display(mz);
	usleep(10000);


	return (0);
}
