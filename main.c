/*
** EPITECH PROJECT, 2017
** my_screensaver_2017
** File description:
** (main.c bootstrap runner)
*/
#include "include/my.h"

void print_my_helper(void)
{
	my_printf("\nWelcome to My_Runner !\n\nIn this game, you are the hero");
	my_printf(", and you are running throught the city.\nDodge obstacles");
	my_printf(" by jumping and try to stay alive as long as you can !");
	my_printf("\nUse SPACE to jump.\n");
	my_printf("\nYou can also create your own map\nThe rules are :\n-Map");
	my_printf("borders must be '#',\n-'O' is for obstacles,\n-'S' is for");
	my_printf("spikes,\n-Your map MUST be 12 char height including border");
	my_printf("s,\n-Your map MUST be 22 char length MINIMUM including bo");
	my_printf("rders,\n-Objects placed under the 10th line won't be count");
	my_printf("ed.\n\nEnjoy !\n\n");
}

int display_lobby(my_w_t *window)
{
	if (window->clocker.seconds >= 1.0/180.0) {
		if (choose_my_menu_or_game(window) != 0)
			return (84);
		sfRenderWindow_display(window->window);
		sfClock_restart(window->clocker.clock);
		analyse_events(window);
	}
	return (0);
}

void destroy_and_free(my_w_t *window)
{
	destroy_my_textures_lib(window);
	destroy_and_free_my_objs(window);
	free_my_map(window);
	destroy_musics(window);
	destroy_my_score(window);
	sfClock_destroy(window->clocker.clock);
	sfRenderWindow_destroy(window->window);
}

int main(int ac, char **av)
{
	my_w_t window = init_my_window();

	if (!window.first || window.error_no != 0 || ac != 2
		|| create_and_load(av[1], &window) != 0) {
		print_my_helper();
		destroy_and_free(&window);
		return (84);
	}
	sfMusic_play(window.audio_lib.game_music);
	sfMusic_setLoop(window.audio_lib.game_music, sfTrue);
	sfRenderWindow_setFramerateLimit(window.window, 120);
	while (sfRenderWindow_isOpen(window.window)) {
		get_time(&window.clocker);
		if (window.game_tools.end_game == sfTrue)
			sfRenderWindow_close(window.window);
		if (display_lobby(&window) != 0)
			return (84);
	}
	destroy_and_free(&window);
	return (0);
}
