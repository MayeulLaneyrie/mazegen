/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nonrecursive.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaneyri <mlaneyri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 20:42:29 by mlaneyri          #+#    #+#             */
/*   Updated: 2023/07/06 22:31:19 by lnr              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mazegen.h"

void floodfill_id(t_maze * mz, int to_replace, int * ids, int replace_with) {
	for (int x = 0; x < mz->w * mz->h; ++x)
		if (ids[x] == to_replace)
			ids[x] = replace_with;
}

int open_door_possible_nonr(t_maze * mz, int * id, int x, int mv) {
	switch (mv) {
		case MV_N:
			return (x >= mz->w && (id[x] != id[x - mz->w]));
		case MV_E:
			return ((x % mz->w < mz->w - 1) && (id[x] != id[x + 1]));
		case MV_S:
	   		return (x < mz->w * (mz->h - 1) && (id[x] != id[x + mz->w]));
		case MV_W:
			return ((x % mz->w) && (id[x] != id[x - 1]));
	}
	return (0);
}

int next_door_nonr(t_maze * mz, int * id, int x) {
	int possible_mvs[4];
	int nof_possible_mvs = 0;

	for (int mv = MV_N; mv <= MV_W; ++mv) {
		if (open_door_possible_nonr(mz, id, x, mv)) {
			possible_mvs[nof_possible_mvs] = mv;
			++nof_possible_mvs;
		}
	}
	if (!nof_possible_mvs)
		return (0);
	return (possible_mvs[rand() % nof_possible_mvs]);
}

void maze_gen_nonr(t_maze * mz) {
	int * id = malloc(mz->h * mz->w * sizeof(int));
	int x;
	int mv;

	for (int i = 0; i < mz->w * mz->h; ++i)
		id[i] = i;
	for (int i = 0; i < mz->w * mz->h - 1; ++i) {
		//maze_display(mz);
		//usleep(10000);
		while (!(mv = next_door_nonr(mz, id, (x = rand() % (mz->w * mz->h)))))
			;
		floodfill_id(mz, id[move_box(mz, x, mv)], id, id[x]);
		open_door(mz, x, mv);
	}
	free(id);
}
