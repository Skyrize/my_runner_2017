/*
** EPITECH PROJECT, 2017
** my_runner_2017
** File description:
** (enter)
*/
#include "include/my.h"

void kill_my_budy(my_w_t *window)
{
	sfMusic_play(AUDIO_L.death_sound);
	GAME_T.ground = 1400;
	GAME_T.jump_state = sfTrue;
}

int get_x_pos(my_w_t *window)
{
	if (GAME_T.jump_x < GAME_T.jump_max
		|| (PLAYER_Y < GAME_T.ground && GAME_T.on_box == sfFalse)) {
		GAME_T.jump_x++;
	} else if (GAME_T.player_pos.y < GAME_T.ground - 100) {
		GAME_T.jump_max += 5;
	} else {
		GAME_T.jump_state = sfFalse;
		BASE.y = GAME_T.ground;
		sfSprite_setPosition(window->player->sp, BASE);
		GAME_T.jump_x = -44;
		GAME_T.jump_max = 44;
	}
	return (GAME_T.jump_x);
}

void jump_baby_jump(my_w_t *window)
{
	int x = 0;

	if (GAME_T.jump_state == sfTrue) {
		x = get_x_pos(window);
		PLAYER_Y = BASE.y -
		(-0.15 * powf(x, 2.) + 290.4);
		sfSprite_setPosition(window->player->sp, GAME_T.player_pos);
		if (GAME_T.ground != 756) {
			sfSprite_rotate(window->player->sp, -3);
		}
		if (PLAYER_Y > 1300) {
			window->menu = END_MENU;
		}
	}
}

void display_player(my_w_t *window)
{
	if (GAME_T.ground == 756)
		move_those_amazing_rect(window->player, window);
	sfSprite_setTextureRect(window->player->sp, window->player->rect);
	sfRenderWindow_drawSprite(window->window, window->player->sp, NULL);
	sfText_setString(SCORE_T.points, my_int_to_array(SCORE_T.score_points));
	sfRenderWindow_drawText(window->window, SCORE_T.score, NULL);
	sfRenderWindow_drawText(window->window, SCORE_T.points, NULL);
	SCORE_T.score_points++;
}
