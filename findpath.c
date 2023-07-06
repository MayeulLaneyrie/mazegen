/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findpath.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaneyri <mlaneyri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 20:42:29 by mlaneyri          #+#    #+#             */
/*   Updated: 2023/07/06 17:36:44 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mazegen.h"

int find_path(t_maze * mz, int xA, int xB, int color) {
	mz->grid[xA] |= color << 4;
	if (xA == xB)
		return (1);
	for (int move = MV_N; move <= MV_W; ++move) {
		if (move_possible(mz, xA, move)
				&& ((mz->grid[move_box(mz, xA, move)] & 0xfa) >> 4) != color)
			if (find_path(mz, move_box(mz, xA, move), xB, color))
				return (1);
	}
	mz->grid[xA] &= 0x0f;
	return (0);
}
