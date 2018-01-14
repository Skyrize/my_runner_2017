/*
** EPITECH PROJECT, 2017
** my_runner_2017
** File description:
** (enter)
*/
#include "include/my.h"

void destroy_obj_and_relink(my_w_t *window, game_objs_t *tmp)
{
	if (tmp->prev) {
		tmp->next->prev = tmp->prev;
		tmp->prev->next = tmp->next;
	} else {
		window->first = tmp->next;
		tmp->next->prev = NULL;
	}
	sfSprite_destroy(tmp->sp);
	free(tmp);
}

void clear_my_game_objs_from_desired(my_w_t *window, my_obj_type_t type)
{
	game_objs_t *tmp = window->first;
	game_objs_t *reader = tmp;

	while (reader->next) {
		reader = tmp->next;
		if (tmp->type == type)
			destroy_obj_and_relink(window, tmp);
		tmp = reader;
	}
}

void restart_game(my_w_t *window)
{
	set_my_map_tools_to_default(window, sfFalse);
	set_my_game_tools_to_default(window);
	sfSprite_setPosition(window->player->sp, GAME_T.player_pos);
	sfSprite_setRotation(window->player->sp, 0);
	clear_my_game_objs_from_desired(window, BOX);
	clear_my_game_objs_from_desired(window, SPIKE);
	sfText_setString(SCORE_T.points, "0");
	SCORE_T.score_points = 0;
}
