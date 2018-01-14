/*
** EPITECH PROJECT, 2017
** my_runner_2017
** File description:
** (enter)
*/
#include "include/my.h"

void create_menu_selector(game_objs_t *obj, sfVector2f *coords)
{
	sfColor reduce_alpha = sfColor_fromRGBA(255, 255, 255, 75);

	if (coords->x == 75) {
		sfSprite_setPosition(obj->sp, *coords);
		sfSprite_setTextureRect(obj->sp, (sfIntRect){0, 0, 300, 85});
	} else {
		sfSprite_setPosition(obj->sp, *coords);
		sfSprite_setColor(obj->sp, reduce_alpha);
	}
}
