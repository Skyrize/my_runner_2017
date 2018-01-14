/*
** EPITECH PROJECT, 2017
** my_runner_2017
** File description:
** (enter)
*/
#include "include/my.h"

void check_if_spike(sfVector2f *obj_pos, game_objs_t *obj, my_w_t *window)
{
	if (GAME_T.ground != 1400 && obj->type == SPIKE) {
		if (PLAYER_X < OBJ_X + 115 && PLAYER_X + 115 > OBJ_X
			&& PLAYER_Y < OBJ_Y + 115 && PLAYER_Y + 137 > OBJ_Y) {
			kill_my_budy(window);
		}
	}
}

int check_if_box(sfVector2f *obj_pos, my_w_t *window)
{
	if (PLAYER_X < OBJ_X + 115 && PLAYER_X + 115 > OBJ_X
		&& PLAYER_Y < OBJ_Y + 167 && PLAYER_Y + 137 > OBJ_Y + 30) {
		if (PLAYER_Y + 137 < OBJ_Y + 70 && PLAYER_Y + 137 > OBJ_Y) {
			GAME_T.on_box = sfTrue;
			GAME_T.jump_state = sfFalse;
			GAME_T.jump_x = -44;
			BASE = sfSprite_getPosition(window->player->sp);
			return (1);
		} else {
			kill_my_budy(window);
		}
	} else {
		GAME_T.on_box = sfFalse;
	}
	return (0);
}

int check_obstacle_pos(sfVector2f *obj_pos, game_objs_t *obj, my_w_t *window)
{
	if (OBJ_X < 450 && OBJ_X > 250) {
		check_if_spike(obj_pos, obj, window);
		if (obj->type == BOX && GAME_T.ground != 1400
			&& (GAME_T.jump_x >= 0 || GAME_T.jump_x == -44)) {
			return (check_if_box(obj_pos, window));
		}
	}
	return (0);
}

void obstacles_reader(my_w_t *window)
{
	game_objs_t *tmp = window->first;
	sfVector2f pos = {0, 0};
	int fall = 0;

	while (tmp) {
		if (tmp->type == SPIKE || tmp->type == BOX) {
			sfRenderWindow_drawSprite(window->window,
				tmp->sp, NULL);
			sfSprite_move(tmp->sp,
				(sfVector2f){tmp->rect_offset, 0});
			pos = sfSprite_getPosition(tmp->sp);
			check_if_out_of_map(&pos, tmp);
			fall += check_obstacle_pos(&pos, tmp, window);
		}
		tmp = tmp->next;
	}
	if (fall == 0 && PLAYER_Y < 755 && GAME_T.jump_state == sfFalse) {
		GAME_T.jump_state = sfTrue;
		GAME_T.jump_x = 42;
	}
}

int display_obstacles(my_w_t *window)
{
	if (MAP_T.map_loader > 21 && GAME_T.ground == 756) {
		if (load_one_more_line(window) != 0)
			return (84);
		MAP_T.map_loader = 1;
	}
	obstacles_reader(window);
	MAP_T.map_loader++;
	return (0);
}
