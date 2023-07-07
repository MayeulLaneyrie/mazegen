/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaneyri <mlaneyri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 20:42:29 by mlaneyri          #+#    #+#             */
/*   Updated: 2023/07/07 15:55:53 by lnr              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mazegen.h"

unsigned long long get_time_us(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (1000000 * tv.tv_sec + tv.tv_usec);
}

int maze_display(t_maze * mz) {
	int mark;


	printf("\e[H\e[34;2m");
	for (int x = 0; x < 2 * mz->w + 1; ++x)
		printf("▄");
	printf("\r\n");
	for (int i = 0; i < mz->w * mz->h; ++i) {
			if (!(i % mz->w))
				printf("█");
			mark = (mz->grid[i] & MARK_X) >> 4;
			if ((mz->grid[i] & DOOR_E) && (mz->grid[i] & DOOR_S))
				printf((mark ? "\e[22;36m▀\e[2;34m▄" : " ▄"));
			else if (mz->grid[i] & DOOR_E)
				printf((mark ? "\e[46m▄\e[49m▄" : "▄▄"));
			else if (mz->grid[i] & DOOR_S)
				printf((mark ? "\e[22;36m▀\e[2;34m█" : " █"));
			else if (move_possible(mz, i, MV_N) || move_possible(mz, i, MV_W))
				printf((mark ? "\e[46m▄\e[49m█" : "▄█"));
			else
				printf("██");
			if (i % mz->w + 1 == mz->w)
				printf("\r\n");
	}
	printf("\e[0m");
	return (0);
}

int move_box(t_maze * mz, int x, int move) {
	return (x + mz->w * ((move == MV_S) - (move == MV_N))
			+ (move == MV_E) - (move == MV_W));
}

void open_door(t_maze * mz, int x, int dir) {
	switch (dir) {
		case MV_N:
			mz->grid[x - mz->w] |= DOOR_S;
			return ;
		case MV_E:
			mz->grid[x] |= DOOR_E;
			return ;
		case MV_S:
			mz->grid[x] |= DOOR_S;
			return ;
		case MV_W:
			mz->grid[x - 1] |= DOOR_E;
	}
}

int move_possible(t_maze * mz, int x, int move) {
	switch (move) {
		case MV_N:
			return (x >= mz->w && mz->grid[x - mz->w] & DOOR_S);
		case MV_E:
			return ((x % mz->w < mz->w - 1) && mz->grid[x] & DOOR_E);
		case MV_S:
	   		return (x < mz->w * (mz->h - 1) && mz->grid[x] & DOOR_S);
		case MV_W:
			return ((x % mz->w) && mz->grid[x - 1] & DOOR_E);
	}
	return (0);
}
