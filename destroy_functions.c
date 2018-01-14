/*
** EPITECH PROJECT, 2017
** my_runner_2017
** File description:
** (enter)
*/
#include "include/my.h"

void destroy_musics(my_w_t *window)
{
	sfMusic_destroy(AUDIO_L.select_sound);
	sfMusic_destroy(AUDIO_L.jump_sound);
	sfMusic_destroy(AUDIO_L.death_sound);
	sfMusic_destroy(AUDIO_L.game_music);
	sfMusic_destroy(AUDIO_L.win_music);
	sfMusic_destroy(AUDIO_L.lose_music);
}

void destroy_my_textures_lib(my_w_t *window)
{
	sfTexture_destroy(TXTR_L.player_tx);
	sfTexture_destroy(TXTR_L.spike_tx);
	sfTexture_destroy(TXTR_L.box_tx);
	sfTexture_destroy(TXTR_L.ground_tx);
	sfTexture_destroy(TXTR_L.forest_tx);
	sfTexture_destroy(TXTR_L.city1_tx);
	sfTexture_destroy(TXTR_L.sky_tx);
	sfTexture_destroy(TXTR_L.switch_on_off_tx);
	sfTexture_destroy(TXTR_L.selector_tx);
	sfTexture_destroy(TXTR_L.main_menu_tx);
	sfTexture_destroy(TXTR_L.pause_exit_tx);
}

void destroy_and_free_my_objs(my_w_t *window)
{
	game_objs_t *tmp;

	while (window->first) {
		tmp = window->first;
		window->first = window->first->next;
		sfSprite_destroy(tmp->sp);
		free(tmp);
	}
}

void free_my_map(my_w_t *window)
{
	if (sfMusic_getLoop(AUDIO_L.game_music) == sfTrue) {
		for (int i = 0; i < 12; i++) {
			free(MAP_T.map[i]);
		}
		free(MAP_T.map);
	}
}

void destroy_my_score(my_w_t *window)
{
	sfText_destroy(SCORE_T.score);
	sfText_destroy(SCORE_T.points);
	sfFont_destroy(SCORE_T.font);
}
