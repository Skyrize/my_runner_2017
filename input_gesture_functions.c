/*
** EPITECH PROJECT, 2017
** my_runner_2017
** File description:
** (enter)
*/
#include "include/my.h"

void change_menu_type(my_w_t *window)
{
	if (window->menu != NONE_MENU) {
		window->menu = NONE_MENU;
	} else {
		window->menu = PAUSE_MENU;
	}
}

void analyse_events(my_w_t *window)
{
	static int x = 0;

	while (sfRenderWindow_pollEvent(window->window, &window->event)) {
		if (window->event.type == sfEvtClosed
			|| sfKeyboard_isKeyPressed(sfKeyEscape) == sfTrue)
			sfRenderWindow_close(window->window);
		if (sfKeyboard_isKeyPressed(sfKeySpace) == sfTrue) {
			GAME_T.jump_state = sfTrue;
			sfMusic_play(AUDIO_L.jump_sound);
		} else if (sfKeyboard_isKeyPressed(sfKeyP) == sfTrue && x == 0
		&& window->menu != MAIN_MENU) {
			change_menu_type(window);
			x++;
		}
	}
	x = 0;
}

void press_on_enter(my_w_t *window, int *selected)
{
	if (sfKeyboard_isKeyPressed(sfKeyReturn) == sfTrue) {
		switch (*selected) {
			case 1:
			check_menu_type_for_action(window);
			break;
			case 2:
			GAME_T.end_game = sfTrue;
			break;
		}
	}
}

void select_mode(my_w_t *window)
{
	sfRenderWindow_pollEvent(window->window, &window->event);
	if (sfKeyboard_isKeyPressed(sfKeyI) == sfTrue
	&& GAME_T.infinite_mode == sfTrue
	&& window->event.type == sfEvtKeyPressed) {
		GAME_T.infinite_mode = sfFalse;
		sfMusic_play(AUDIO_L.select_sound);
	} else if (sfKeyboard_isKeyPressed(sfKeyI) == sfTrue
	&& GAME_T.infinite_mode == sfFalse
	&& window->event.type == sfEvtKeyPressed) {
		GAME_T.infinite_mode = sfTrue;
		sfMusic_play(AUDIO_L.select_sound);
	}
}

void select_choice(my_w_t *window, int *selected, my_obj_type_t *menu_type)
{
	press_on_enter(window, selected);
	if (sfKeyboard_isKeyPressed(sfKeyUp) == sfTrue) {
		*selected = 1;
		sfMusic_play(AUDIO_L.select_sound);
	} else if (sfKeyboard_isKeyPressed(sfKeyDown) == sfTrue) {
		*selected = 2;
		sfMusic_play(AUDIO_L.select_sound);
	}
	if (*menu_type == MAIN) {
		select_mode(window);
		sfRenderWindow_drawSprite(window->window,
			window->switcher->sp, NULL);
	}
}
