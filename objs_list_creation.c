/*
** EPITECH PROJECT, 2017
** my_runner_2017
** File description:
** (enter)
*/
#include "include/my.h"

void detect_type(game_objs_t *obj, sfVector2f *coords)
{
	switch (obj->type) {
	case PLAYER:
		create_player(obj, coords);
		break;
	case BACKGROUND:
		create_background(obj);
		break;
	case BOX:
		create_box(obj, coords);
		break;
	case SPIKE:
		create_spike(obj, coords);
		break;
	case MENU_SELECTOR:
		create_menu_selector(obj, coords);
		break;
	default:
	create_menu(obj, coords);
	break;
	}
}

game_objs_t *init_game_objs(sfTexture *texture, my_obj_type_t type,
	sfVector2f *coords)
{
	game_objs_t *new_obj = malloc(sizeof(game_objs_t));

	if (new_obj == NULL)
		return (NULL);
	new_obj->type = type;
	new_obj->rect = (sfIntRect){0, 0, 0, 0};
	new_obj->rect_max_value = 0;
	new_obj->rect_offset = 0;
	new_obj->sp = sfSprite_create();
	sfSprite_setTexture(new_obj->sp, texture, sfTrue);
	detect_type(new_obj, coords);
	new_obj->next = NULL;
	new_obj->prev = NULL;
	return (new_obj);
}

int add_to_list(sfTexture *texture, my_obj_type_t type,
	my_w_t *window, sfVector2f coords)
{
	game_objs_t *new_obj = init_game_objs(texture, type, &coords);

	if (new_obj == NULL)
		return (84);
	new_obj->next = window->first;
	if (new_obj->type == PLAYER)
		window->player = new_obj;
	else if (new_obj->type == MENU_SELECTOR && coords.x == 75) {
		window->switcher = new_obj;
	} else if (new_obj->type == MENU_SELECTOR)
		window->selector = new_obj;
	if (new_obj->next != NULL)
		new_obj->next->prev = new_obj;
	window->first = new_obj;
	return (0);
}

void init_my_game_objects_list(my_w_t *window)
{
	window->error_no += add_to_list(TXTR_L.player_tx,
	PLAYER, window, (sfVector2f){288, 756});
	window->error_no += add_to_list(TXTR_L.ground_tx,
	BACKGROUND, window, (sfVector2f){0, 0});
	window->error_no += add_to_list(TXTR_L.forest_tx,
	BACKGROUND, window, (sfVector2f){0, 0});
	window->error_no += add_to_list(TXTR_L.city1_tx,
	BACKGROUND, window, (sfVector2f){0, 0});
	window->error_no += add_to_list(TXTR_L.sky_tx,
	BACKGROUND, window, (sfVector2f){0, 0});
}
