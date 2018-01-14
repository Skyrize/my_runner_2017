/*
** EPITECH PROJECT, 2017
** my_screensaver_2017
** File description:
** (main.c bootstrap runner)
*/
#include "include/my.h"

void move_rect_left(game_objs_t *rect)
{
	if (rect->rect.left < rect->rect_max_value) {
		rect->rect.left += rect->rect_offset;
	}
	if (rect->rect.left >= rect->rect_max_value) {
		rect->rect.left = 0;
	}
}

void get_time(ctime_t *clocker)
{
	clocker->timer = sfClock_getElapsedTime(clocker->clock);
	clocker->seconds = clocker->timer.microseconds / 1000000.0;
}

ctime_t init_timer(void)
{
	ctime_t clock;

	clock.clock = sfClock_create();
	clock.seconds = 0;
	return (clock);
}

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

void init_my_audio_lib(my_w_t *window)
{
	AUDIO_L.select_sound = sfMusic_createFromFile("sounds/select.ogg");
	AUDIO_L.jump_sound = sfMusic_createFromFile("sounds/jump.ogg");
	AUDIO_L.death_sound = sfMusic_createFromFile("sounds/death.ogg");
	AUDIO_L.game_music = sfMusic_createFromFile("sounds/undertale.ogg");
	AUDIO_L.lose_music = sfMusic_createFromFile("sounds/lose.ogg");
	AUDIO_L.win_music = sfMusic_createFromFile("sounds/win.ogg");
}

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

void move_those_amazing_rect(game_objs_t *tmp, my_w_t *window)
{
	static unsigned int no_clock_pro = 0;

	if (tmp->type == PLAYER
		&& no_clock_pro > 40 && GAME_T.jump_state == sfFalse) {
		move_rect_left(tmp);
		no_clock_pro = 0;
	}
	if (tmp->type == BACKGROUND)
		move_rect_left(tmp);
	no_clock_pro++;
}

int seek_objs(my_w_t *window, int i)
{
	int error_no = 0;

	if (MAP_T.map[i][MAP_T.map_reader] == 'S') {
		error_no = add_to_list(TXTR_L.spike_tx, SPIKE, window,
		(sfVector2f){2016, (i - 1) * 108});
	} else if (MAP_T.map[i][MAP_T.map_reader] == 'O') {
		error_no = add_to_list(TXTR_L.box_tx, BOX, window,
		(sfVector2f){2016, ((i - 1) * 108) - 30});
	}
	if (error_no != 0)
		return (error_no);
	return (0);
}

int accelerate_my_game(my_w_t *window)
{
	game_objs_t *tmp = window->first;

	while (tmp) {
		if (tmp->type == PLAYER || tmp->type == BACKGROUND)
			tmp->rect_offset++;
		if (tmp->type == BOX || tmp->type == SPIKE)
			tmp->rect_offset--;
		tmp = tmp->next;
	}
	return (0);
}

int load_one_more_line(my_w_t *window)
{
	if (MAP_T.map_reader > MAP_T.map_length - 1
		&& GAME_T.infinite_mode == sfTrue) {
		MAP_T.map_reader = 1;
		accelerate_my_game(window);
	}
	for (int i = 1; i < 11; i++) {
		if (seek_objs(window, i) != 0)
			return (84);
	}
	MAP_T.map_reader++;
	return (0);
}

void check_if_out_of_map(sfVector2f *pos, game_objs_t *obj)
{
	if (pos->x < -115) {
		if (obj->next) {
			obj->next->prev = obj->prev;
		}
		if (obj->prev) {
			obj->prev->next = obj->next;
			sfSprite_destroy(obj->sp);
		}
	}
}

void kill_my_budy(my_w_t *window)
{
	sfMusic_play(AUDIO_L.death_sound);
	GAME_T.ground = 1400;
	GAME_T.jump_state = sfTrue;
}

void check_if_spike(sfVector2f *obj_pos, game_objs_t *obj, my_w_t *window)
{
	if (GAME_T.ground != 1400 && obj->type == SPIKE) {
		if (PLAYER_X < OBJ_X + 115 && PLAYER_X + 115 > OBJ_X
			&& PLAYER_Y < OBJ_Y + 115 && PLAYER_Y + 137 > OBJ_Y) {
			kill_my_budy(window);
		}
	}
}

int check_if_box(sfVector2f *obj_pos, my_w_t *window)
{
	if (PLAYER_X < OBJ_X + 115 && PLAYER_X + 115 > OBJ_X
		&& PLAYER_Y < OBJ_Y + 167 && PLAYER_Y + 137 > OBJ_Y + 30) {
		if (PLAYER_Y + 137 < OBJ_Y + 70 && PLAYER_Y + 137 > OBJ_Y) {
			GAME_T.on_box = sfTrue;
			GAME_T.jump_state = sfFalse;
			GAME_T.jump_x = -44;
			BASE = sfSprite_getPosition(window->player->sp);
			return (1);
		} else {
			kill_my_budy(window);
		}
	} else {
		GAME_T.on_box = sfFalse;
	}
	return (0);
}

int check_obstacle_pos(sfVector2f *obj_pos, game_objs_t *obj, my_w_t *window)
{
	if (OBJ_X < 450 && OBJ_X > 250) {
		check_if_spike(obj_pos, obj, window);
		if (obj->type == BOX && GAME_T.ground != 1400
			&& (GAME_T.jump_x >= 0 || GAME_T.jump_x == -44)) {
			return (check_if_box(obj_pos, window));
		}
	}
	return (0);
}

void obstacles_reader(my_w_t *window)
{
	game_objs_t *tmp = window->first;
	sfVector2f pos = {0, 0};
	int fall = 0;

	while (tmp) {
		if (tmp->type == SPIKE || tmp->type == BOX) {
			sfRenderWindow_drawSprite(window->window,
				tmp->sp, NULL);
			sfSprite_move(tmp->sp,
				(sfVector2f){tmp->rect_offset, 0});
			pos = sfSprite_getPosition(tmp->sp);
			check_if_out_of_map(&pos, tmp);
			fall += check_obstacle_pos(&pos, tmp, window);
		}
		tmp = tmp->next;
	}
	if (fall == 0 && PLAYER_Y < 755 && GAME_T.jump_state == sfFalse) {
		GAME_T.jump_state = sfTrue;
		GAME_T.jump_x = 42;
	}
}

int display_obstacles(my_w_t *window)
{
	if (MAP_T.map_loader > 21 && GAME_T.ground == 756) {
		if (load_one_more_line(window) != 0)
			return (84);
		MAP_T.map_loader = 1;
	}
	obstacles_reader(window);
	MAP_T.map_loader++;
	return (0);
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

int read_list_and_display_objs(my_w_t *window)
{
	game_objs_t *tmp = window->first;

	while (tmp) {
		if (tmp->type == BACKGROUND) {
			move_those_amazing_rect(tmp, window);
			sfSprite_setTextureRect(tmp->sp, tmp->rect);
			sfRenderWindow_drawSprite(window->window,
				tmp->sp, NULL);
		}
		tmp = tmp->next;
	}
	if (display_obstacles(window) != 0)
		return (84);
	display_player(window);
	return (0);
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

void read_buffer(char *buf, my_w_t *window)
{
	for (int i = 0; i < 512; i++, MAP_T.map_length++) {
		if (buf[i] == '\n') {
			break;
		}
	}
}

int create_and_load(char *str, my_w_t *window)
{
	int fd = open(str, O_RDONLY);
	char buf[512];

	if (fd == -1)
		return (84);
	while (MAP_T.map_length % 512 == 0) {
		read(fd, buf, 512);
		read_buffer(buf, window);
	}
	close(fd);
	fd = open(str, O_RDONLY);
	for (int i = 0; i < 12; i++) {
		MAP_T.map[i] = malloc(sizeof(char)
		* (MAP_T.map_length + 1));
		if (!MAP_T.map[i])
			return (84);
		read(fd, MAP_T.map[i], MAP_T.map_length + 1);
		MAP_T.map[i][MAP_T.map_length] = 0;
	}
	return (0);
}

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

int compute_and_display_game(my_w_t *window)
{
	jump_baby_jump(window);
	if (read_list_and_display_objs(window) != 0)
		return (84);
	return (0);
}

void destroy_obj_and_relink(my_w_t *window, game_objs_t *tmp)
{
	if (tmp->prev) {
		tmp->next->prev = tmp->prev;
		tmp->prev->next = tmp->next;
	} else {
		window->first = tmp->next;
		tmp->next->prev = NULL;
	}
	sfSprite_destroy(tmp->sp);
	free(tmp);
}

void clear_my_game_objs_from_desired(my_w_t *window, my_obj_type_t type)
{
	game_objs_t *tmp = window->first;
	game_objs_t *reader = tmp;

	while (reader->next) {
		reader = tmp->next;
		if (tmp->type == type)
			destroy_obj_and_relink(window, tmp);
		tmp = reader;
	}
}

void restart_game(my_w_t *window)
{
	set_my_map_tools_to_default(window, sfFalse);
	set_my_game_tools_to_default(window);
	sfSprite_setPosition(window->player->sp, GAME_T.player_pos);
	sfSprite_setRotation(window->player->sp, 0);
	clear_my_game_objs_from_desired(window, BOX);
	clear_my_game_objs_from_desired(window, SPIKE);
	sfText_setString(SCORE_T.points, "0");
	SCORE_T.score_points = 0;
}

void check_menu_type_for_action(my_w_t *window)
{
	if (window->menu != MAIN_MENU)
		restart_game(window);
	window->menu = NONE_MENU;
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
		sfRenderWindow_drawSprite(window->window, window->switcher->sp, NULL);
	}
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
