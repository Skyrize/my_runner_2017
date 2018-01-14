/*
** EPITECH PROJECT, 2017
** my_runner_2017
** File description:
** (enter)
*/
#include "include/my.h"

ctime_t init_timer(void)
{
	ctime_t clock;

	clock.clock = sfClock_create();
	clock.seconds = 0;
	return (clock);
}

void init_my_audio_lib(my_w_t *window)
{
	AUDIO_L.select_sound = sfMusic_createFromFile("sounds/select.ogg");
	AUDIO_L.jump_sound = sfMusic_createFromFile("sounds/jump.ogg");
	AUDIO_L.death_sound = sfMusic_createFromFile("sounds/death.ogg");
	AUDIO_L.game_music = sfMusic_createFromFile("sounds/undertale.ogg");
	AUDIO_L.lose_music = sfMusic_createFromFile("sounds/lose.ogg");
	AUDIO_L.win_music = sfMusic_createFromFile("sounds/win.ogg");
}

void add_menus_to_list(my_w_t *window)
{
	window->menu = MAIN_MENU;
	window->error_no += add_to_list(TXTR_L.switch_on_off_tx,
	MENU_SELECTOR, window, (sfVector2f){75, 655});
	window->error_no += add_to_list(TXTR_L.selector_tx,
	MENU_SELECTOR, window, (sfVector2f){545, 125});
	window->error_no += add_to_list(TXTR_L.main_menu_tx, MAIN,
	window, (sfVector2f){0, 0});
	window->error_no += add_to_list(TXTR_L.pause_exit_tx, PAUSE,
	window, (sfVector2f){0, 0});
	window->error_no += add_to_list(TXTR_L.pause_exit_tx, END,
	window, (sfVector2f){0, 0});
}

void init_my_textures_lib(my_w_t *window)
{
	TXTR_L.player_tx = sfTexture_createFromFile("txtrs/runner.png", NULL);
	TXTR_L.spike_tx = sfTexture_createFromFile("txtrs/spike.png", NULL);
	TXTR_L.box_tx = sfTexture_createFromFile("txtrs/box.png", NULL);
	TXTR_L.ground_tx = sfTexture_createFromFile("txtrs/ground.png", NULL);
	TXTR_L.forest_tx = sfTexture_createFromFile("txtrs/forest.png", NULL);
	TXTR_L.city1_tx = sfTexture_createFromFile("txtrs/city1.png", NULL);
	TXTR_L.sky_tx = sfTexture_createFromFile("txtrs/sky.png", NULL);
	TXTR_L.switch_on_off_tx = sfTexture_createFromFile(
		"txtrs/on-off-switch.png", NULL);
	TXTR_L.selector_tx = sfTexture_createFromFile("txtrs/selector.png",
	NULL);
	TXTR_L.main_menu_tx = sfTexture_createFromFile("txtrs/main_menu.png",
	NULL);
	TXTR_L.pause_exit_tx = sfTexture_createFromFile("txtrs/pause_exit.png",
	NULL);
}

my_w_t init_my_window(void)
{
	my_w_t window;

	window.error_no = 0;
	window.first = NULL;
	window.game_tools.infinite_mode = sfFalse;
	window.clocker = init_timer();
	window.window = sfRenderWindow_create((sfVideoMode){1920, 1080, 32},
	"Central Park Rush", sfResize | sfClose, NULL);
	set_my_score_to_zero(&window);
	init_my_textures_lib(&window);
	set_my_map_tools_to_default(&window, sfTrue);
	set_my_game_tools_to_default(&window);
	init_my_audio_lib(&window);
	init_my_game_objects_list(&window);
	add_menus_to_list(&window);
	return (window);
}
