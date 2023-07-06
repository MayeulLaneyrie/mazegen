/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaneyri <mlaneyri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 20:42:29 by mlaneyri          #+#    #+#             */
/*   Updated: 2023/07/06 17:57:10 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mazegen.h"

int open_door_possible(t_maze * mz, int x, int mv) {
	switch (mv) {
		case MV_N:
			return (x >= mz->w && !IS_EXPLORD(mz, x - mz->w));
		case MV_E:
			return ((x % mz->w < mz->w - 1) && !IS_EXPLORD(mz, x + 1));
		case MV_S:
	   		return (x < mz->w * (mz->h - 1) && !IS_EXPLORD(mz, x + mz->w));
		case MV_W:
			return ((x % mz->w) && !IS_EXPLORD(mz, x - 1));
	}
	return (0);
}

int next_door(t_maze * mz, int x) {
	int possible_mvs[4];
	int nof_possible_mvs = 0;

	for (int mv = MV_N; mv <= MV_W; ++mv) {
		if (open_door_possible(mz, x, mv)) {
			possible_mvs[nof_possible_mvs] = mv;
			++nof_possible_mvs;
		}
	}
	if (!nof_possible_mvs)
		return (0);
	return (possible_mvs[rand() % nof_possible_mvs]);
}

void maze_gen_r(t_maze * mz, int x) {
	int mv;

	maze_display(mz);
	usleep(10000);
	mz->grid[x] |= EXPLORD;
	while ((mv = next_door(mz, x))) {
		open_door(mz, x, mv);
		maze_gen_r(mz, move_box(mz, x, mv));
	}
}
