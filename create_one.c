/*
** EPITECH PROJECT, 2017
** my_runner_2017
** File description:
** (enter)
*/
#include "include/my.h"

void create_player(game_objs_t *obj, sfVector2f *coords)
{
	obj->rect = (sfIntRect){0, 0, 115, 137};
	obj->rect_max_value = 920;
	obj->rect_offset = 115;
	sfSprite_setPosition(obj->sp, *coords);
}

void create_background(game_objs_t *obj)
{
	static int offset = 5;

	obj->rect = (sfIntRect){0, 0, 1920, 1080};
	sfSprite_setTextureRect(obj->sp, obj->rect);
	obj->rect_offset = offset;
	obj->rect_max_value = 1920;
	offset -= 2;
}

void create_box(game_objs_t *obj, sfVector2f *coords)
{
	obj->rect_offset = -5;
	sfSprite_setPosition(obj->sp, *coords);
}

void create_spike(game_objs_t *obj, sfVector2f *coords)
{
	obj->rect_offset = -5;
	sfSprite_setPosition(obj->sp, *coords);
}

void create_menu(game_objs_t *obj, sfVector2f *coords)
{
	sfSprite_setPosition(obj->sp, *coords);
}
