/*
** EPITECH PROJECT, 2017
** my_runner_2017
** File description:
** (enter)
*/
#include "include/my.h"

void set_my_game_tools_to_default(my_w_t *window)
{
	GAME_T.ground = 756;
	GAME_T.jump_x = -44;
	GAME_T.jump_max = 44;
	GAME_T.end_game = sfFalse;
	GAME_T.jump_state = sfFalse;
	GAME_T.on_box = sfFalse;
	GAME_T.player_pos = (sfVector2f){288, 756};
	GAME_T.player_base_pos = (sfVector2f){288, 756};
}

void set_my_map_tools_to_default(my_w_t *window, sfBool init)
{
	MAP_T.map_loader = 1;
	MAP_T.map_reader = 1;
	if (init == sfTrue) {
		MAP_T.map_length = 0;
		MAP_T.map = malloc(sizeof(char *) * 12);
		if (!MAP_T.map)
			window->error_no = 84;
	}
}

void set_my_score_to_zero(my_w_t *window)
{
	SCORE_T.score_points = 0;
	SCORE_T.font = sfFont_createFromFile("font/ARCADECLASSIC.TTF");
	SCORE_T.score = sfText_create();
	SCORE_T.points = sfText_create();
	sfText_setString(SCORE_T.score, "YOUR   POINTS");
	sfText_setString(SCORE_T.points, "0");
	sfText_setFont(SCORE_T.score, SCORE_T.font);
	sfText_setFont(SCORE_T.points, SCORE_T.font);
	sfText_setCharacterSize(SCORE_T.score, 60);
	sfText_setCharacterSize(SCORE_T.points, 60);
	sfText_setPosition(SCORE_T.score, (sfVector2f){300, 880});
	sfText_setPosition(SCORE_T.points, (sfVector2f){300, 970});
}
