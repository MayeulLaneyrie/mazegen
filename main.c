/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaneyri <mlaneyri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 20:42:29 by mlaneyri          #+#    #+#             */
/*   Updated: 2023/07/06 19:18:41 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mazegen.h"
#include <errno.h>
#include <signal.h>

void cursorvisible(int signum) {
	(void)signum;
	printf("\e[?25h\e[2J\e[H");
	exit(0);
}

int main(int ac, char **av) {
	t_maze mz;

	signal(SIGINT, cursorvisible);
	printf("\e[2J\e[?25l");
	if (ac < 3)
		die("sds", __FILE__, __LINE__, "Usage: ./mazegen w h\n");
	mz.w = atoi(av[1]);
	mz.h = atoi(av[2]);
	if (!mz.w || !mz.h)
		die("sds", __FILE__, __LINE__, "Invalid value: 0\n");
	if (ac > 3)
		srand(atoi(av[3]));
	else
		srand(get_time_us());
	mz.grid = malloc(mz.w * mz.h);
	for (int i = 0; i < mz.w * mz.h; ++i)
		mz.grid[i] = 0;
	maze_gen_r(&mz, rand() % (mz.w * mz.h));
	//maze_gen_nonr(&mz);
	maze_display(&mz);
	//find_path(&mz, 0, mz.w * mz.h - 1, 1);
	maze_display(&mz);
	free(mz.grid);
	printf("\e[?25h");
	return (0);
}
