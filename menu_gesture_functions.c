/*
** EPITECH PROJECT, 2017
** my_runner_2017
** File description:
** (enter)
*/
#include "include/my.h"

void check_menu_type_for_action(my_w_t *window)
{
	if (window->menu != MAIN_MENU)
		restart_game(window);
	window->menu = NONE_MENU;
}

void display_selectors(my_w_t *window, int selected)
{
	static sfVector2f selector_pos_up = {545, 125};
	static sfVector2f selector_pos_down = {545, 595};

	if (selected == 1) {
		sfSprite_setPosition(window->selector->sp, selector_pos_up);
	} else if (selected == 2)
		sfSprite_setPosition(window->selector->sp, selector_pos_down);
	if (GAME_T.infinite_mode == sfTrue) {
		sfSprite_setTextureRect(window->switcher->sp,
			(sfIntRect){0, 0, 300, 85});
	} else {
		sfSprite_setTextureRect(window->switcher->sp,
			(sfIntRect){0, 85, 300, 85});
	}
	sfRenderWindow_drawSprite(window->window, window->selector->sp, NULL);
}

void display_menu_type(my_w_t *window, my_obj_type_t menu_type)
{
	game_objs_t *tmp = window->first;
	static int selected = 1;

	while (tmp) {
		if (tmp->type == menu_type)
			sfRenderWindow_drawSprite(window->window,
				tmp->sp, NULL);
		tmp = tmp->next;
	}
	display_selectors(window, selected);
	select_choice(window, &selected, &menu_type);
}

int choose_my_menu_or_game(my_w_t *window)
{
	int error_no = 0;

	switch (window->menu) {
		case NONE_MENU:
		error_no = compute_and_display_game(window);
		break;
		case MAIN_MENU:
		display_menu_type(window, MAIN);
		break;
		case PAUSE_MENU:
		display_menu_type(window, PAUSE);
		break;
		case END_MENU:
		display_menu_type(window, END);
		sfRenderWindow_drawText(window->window, SCORE_T.score, NULL);
		sfRenderWindow_drawText(window->window, SCORE_T.points, NULL);
		break;
	}
	return (error_no);
}
