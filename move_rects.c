/*
** EPITECH PROJECT, 2017
** my_runner_2017
** File description:
** (enter)
*/
#include "include/my.h"

void move_rect_left(game_objs_t *rect)
{
	if (rect->rect.left < rect->rect_max_value) {
		rect->rect.left += rect->rect_offset;
	}
	if (rect->rect.left >= rect->rect_max_value) {
		rect->rect.left = 0;
	}
}

void move_those_amazing_rect(game_objs_t *tmp, my_w_t *window)
{
	static unsigned int no_clock_pro = 0;

	if (tmp->type == PLAYER
		&& no_clock_pro > 40 && GAME_T.jump_state == sfFalse) {
		move_rect_left(tmp);
		no_clock_pro = 0;
	}
	if (tmp->type == BACKGROUND)
		move_rect_left(tmp);
	no_clock_pro++;
}
