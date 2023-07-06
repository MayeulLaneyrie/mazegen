/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mazegen.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaneyri <mlaneyri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 20:42:29 by mlaneyri          #+#    #+#             */
/*   Updated: 2023/07/06 18:43:52 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "./die.h"

#define MV_N 1
#define MV_E 2
#define MV_S 3
#define MV_W 4

#define DOOR_E 0x01
#define DOOR_S 0x02
#define EXPLORD 0x04
#define MARK_X 0xf0
#define MARK_A 0x10
#define MARK_B 0x20
#define MARK_C 0x40
#define MARK_D 0x80

#define IS_EXPLORD(MZ, X) ((MZ)->grid[(X)] & EXPLORD)
#define SYMMETRY(MZ, X) ((MZ)->w * (MZ)->h - (X) - 1)

typedef struct s_maze {
	char * grid;
	int w;
	int h;
} t_maze;

/*
**	common.c
*/

unsigned long long get_time_us(void);
int maze_display(t_maze * mz);
int move_box(t_maze * mz, int x, int move);
int move_possible(t_maze * mz, int x, int move);
void open_door(t_maze * mz, int x, int move);

/*
**	recursive.c
*/

int open_door_possible(t_maze * mz, int x, int mv);
int next_door(t_maze * mz, int x);
void maze_gen_r(t_maze * mz, int x);

/*
**	nonrecursive.c
*/

void floodfill_id(t_maze * mz, int x, int * ids, int id);
int open_door_possible_nonr(t_maze * mz, int * id, int x, int mv);
int next_door_nonr(t_maze * mz, int * id, int x);
void maze_gen_nonr(t_maze * mz);

/*
**	findpath.c
*/

int find_path(t_maze * mz, int xA, int xB, int color);
