/*
** EPITECH PROJECT, 2017
** my_runner_2017
** File description:
** (enter)
*/
#include "include/my.h"

void get_time(ctime_t *clocker)
{
	clocker->timer = sfClock_getElapsedTime(clocker->clock);
	clocker->seconds = clocker->timer.microseconds / 1000000.0;
}

int accelerate_my_game(my_w_t *window)
{
	game_objs_t *tmp = window->first;

	while (tmp) {
		if (tmp->type == PLAYER || tmp->type == BACKGROUND)
			tmp->rect_offset++;
		if (tmp->type == BOX || tmp->type == SPIKE)
			tmp->rect_offset--;
		tmp = tmp->next;
	}
	return (0);
}

void check_if_out_of_map(sfVector2f *pos, game_objs_t *obj)
{
	if (pos->x < -115) {
		if (obj->next) {
			obj->next->prev = obj->prev;
		}
		if (obj->prev) {
			obj->prev->next = obj->next;
			sfSprite_destroy(obj->sp);
		}
	}
}

int read_list_and_display_objs(my_w_t *window)
{
	game_objs_t *tmp = window->first;

	while (tmp) {
		if (tmp->type == BACKGROUND) {
			move_those_amazing_rect(tmp, window);
			sfSprite_setTextureRect(tmp->sp, tmp->rect);
			sfRenderWindow_drawSprite(window->window,
				tmp->sp, NULL);
		}
		tmp = tmp->next;
	}
	if (display_obstacles(window) != 0)
		return (84);
	display_player(window);
	return (0);
}

int compute_and_display_game(my_w_t *window)
{
	jump_baby_jump(window);
	if (read_list_and_display_objs(window) != 0)
		return (84);
	return (0);
}
