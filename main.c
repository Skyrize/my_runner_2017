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

	sfSprite_setPosition(obj->sp, *coords);
	sfSprite_setColor(obj->sp, reduce_alpha);
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

game_objs_t *init_game_objs(const char *path_to_spritesheet, my_obj_type_t type,
	sfVector2f *coords)
{
	game_objs_t *new_obj = malloc(sizeof(game_objs_t));

	if (new_obj == NULL)
		return (NULL);
	new_obj->type = type;
	new_obj->sp = sfSprite_create();
	new_obj->tx = sfTexture_createFromFile(path_to_spritesheet, NULL);
	sfSprite_setTexture(new_obj->sp, new_obj->tx, sfTrue);
	detect_type(new_obj, coords);
	new_obj->prev = NULL;
	return (new_obj);
}

int add_to_list(const char *path_to_spritesheet, my_obj_type_t type,
	my_w_t *window, sfVector2f coords)
{
	game_objs_t *new_obj = init_game_objs(path_to_spritesheet,
		type, &coords);

	if (new_obj == NULL)
		return (84);
	new_obj->next = window->first;
	if (new_obj->type == PLAYER)
		window->player = new_obj;
	else if (new_obj->type == MENU_SELECTOR)
		window->selector = new_obj;
	if (new_obj->next != NULL)
		new_obj->next->prev = new_obj;
	window->first = new_obj;
	return (0);
}

void init_my_game_objects_list(my_w_t *window)
{
	window->error_no += add_to_list("textures/runner.png",
	PLAYER, window, (sfVector2f){288, 756});
	window->error_no += add_to_list("textures/ground.png",
	BACKGROUND, window, (sfVector2f){0, 0});
	window->error_no += add_to_list("textures/forest.png",
	BACKGROUND, window, (sfVector2f){0, 0});
	window->error_no += add_to_list("textures/city1.png",
	BACKGROUND, window, (sfVector2f){0, 0});
	window->error_no += add_to_list("textures/sky.png",
	BACKGROUND, window, (sfVector2f){0, 0});
}

void init_my_music(my_w_t *window)
{
	window->select_sound = sfMusic_createFromFile("sounds/select.ogg");
	window->jump_sound = sfMusic_createFromFile("sounds/jump.ogg");
	window->death_sound = sfMusic_createFromFile("sounds/death.ogg");
	window->game_music = sfMusic_createFromFile("sounds/undertale.ogg");
	window->lose_music = sfMusic_createFromFile("sounds/lose.ogg");
	window->win_music = sfMusic_createFromFile("sounds/win.ogg");
}

void set_my_player_states_and_jump_to_default(my_w_t *window)
{
	window->ground = 756;
	window->jump_x = -44;
	window->jump_state = sfFalse;
	window->on_box = sfFalse;
	window->player_pos = (sfVector2f){288, 756};
	window->player_base_pos = (sfVector2f){288, 756};
}

void add_menus_to_list(my_w_t *window)
{
	window->menu = MAIN_MENU;
	window->error_no += add_to_list("textures/selector.png",
	MENU_SELECTOR, window, (sfVector2f){545, 125});
	window->error_no += add_to_list("textures/main_menu.png", MAIN,
	window, (sfVector2f){0, 0});
	window->error_no += add_to_list("textures/pause_exit.png", PAUSE,
	window, (sfVector2f){0, 0});
	window->error_no += add_to_list("textures/pause_exit.png", END,
	window, (sfVector2f){0, 0});
	window->error_no += add_to_list("textures/pause_exit.png", END,
	window, (sfVector2f){0, 0});
	window->error_no += add_to_list("textures/pause_exit.png", END,
	window, (sfVector2f){0, 0});
}

void set_my_map_states_to_default(my_w_t *window)
{
	window->map_length = 0;
	window->map_loader = 1;
	window->map_reader = 1;
}

my_w_t init_my_window(void)
{
	my_w_t window;

	window.error_no = 0;
	window.end_game = sfFalse;
	set_my_map_states_to_default(&window);
	set_my_player_states_and_jump_to_default(&window);
	window.window = sfRenderWindow_create((sfVideoMode){1920, 1080, 32},
	"Central Park Rush", sfResize | sfClose, NULL);
	window.clocker = init_timer();
	window.first = NULL;
	init_my_music(&window);
	window.map = malloc(sizeof(char *) * 12);
	if (!window.map)
		window.error_no = 84;
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
			window->jump_state = sfTrue;
			sfMusic_play(window->jump_sound);
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
		&& no_clock_pro > 40 && window->jump_state == sfFalse) {
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

	if (window->map[i][window->map_reader] == 'S') {
		error_no = add_to_list("textures/spike.png", SPIKE, window,
		(sfVector2f){2016, (i - 1) * 108});
	} else if (window->map[i][window->map_reader] == 'O') {
		error_no = add_to_list("textures/box.png", BOX, window,
		(sfVector2f){2016, ((i - 1) * 108) - 30});
	}
	if (error_no != 0)
		return (error_no);
	return (0);
}

int load_one_more_line(my_w_t *window)
{
	if (window->map_reader > window->map_length - 1) {
		window->map_reader = 1;
	}
	for (int i = 1; i < 11; i++) {
		if (seek_objs(window, i) != 0)
			return (84);
	}
	window->map_reader++;
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
			sfTexture_destroy(obj->tx);
		}
	}
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

int check_if_spike(sfVector2f *obj_pos, game_objs_t *obj, my_w_t *window)
{
	if (window->ground != 1400) {
		if (obj->type == SPIKE && OBJ_X >= 290 && OBJ_X <= 405
			&& ((PLAYER_Y + 137 >= OBJ_Y
				&& PLAYER_Y + 137 <= OBJ_Y + 137)
				|| (PLAYER_Y >= OBJ_Y
					&& PLAYER_Y <= OBJ_Y + 137))) {
			sfMusic_play(window->death_sound);
			window->ground = 1400;
			window->jump_state = sfTrue;
		}
	}
	return (0);
}

int check_obstacle_pos(sfVector2f *obj_pos, game_objs_t *obj, my_w_t *window)
{
	check_if_spike(obj_pos, obj, window);
	if (obj->type == BOX && window->ground != 1400
		&& OBJ_X <= 403 && OBJ_X >= 260) {
		if (PLAYER_Y + 137 >= OBJ_Y + 30
			&& PLAYER_Y + 137 <= OBJ_Y + 45
			&& (window->jump_x >= 0 || window->jump_x == -44)) {
			window->on_box = sfTrue;
			window->jump_state = sfFalse;
			window->jump_x = -44;
			BASE = sfSprite_getPosition(window->player->sp);
			return (1);
		} else {
			window->on_box = sfFalse;
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
	if (fall == 0 && PLAYER_Y < 755 && window->jump_state == sfFalse) {
		window->jump_state = sfTrue;
		window->jump_x = 43;
	}
}

int display_obstacles(my_w_t *window)
{
	if (window->map_loader > 21 && window->ground == 756) {
		if (load_one_more_line(window) != 0)
			return (84);
		window->map_loader = 1;
	}
	obstacles_reader(window);
	window->map_loader++;
	return (0);
}

void display_player(my_w_t *window)
{
	if (window->ground == 756)
		move_those_amazing_rect(window->player, window);
	sfSprite_setTextureRect(window->player->sp, window->player->rect);
	sfRenderWindow_drawSprite(window->window, window->player->sp, NULL);
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
	static int max = 44;

	if (window->jump_x < max
		|| (PLAYER_Y < window->ground && window->on_box == sfFalse)) {
		window->jump_x++;
	} else if (window->player_pos.y < window->ground) {
		max += 5;
	} else {
		window->jump_state = sfFalse;
		BASE.y = window->ground;
		sfSprite_setPosition(window->player->sp, BASE);
		window->jump_x = -44;
		max = 44;
	}
	return (window->jump_x);
}

void jump_baby_jump(my_w_t *window)
{
	int x = 0;

	if (window->jump_state == sfTrue) {
		x = get_x_pos(window);
		PLAYER_Y = BASE.y -
		(-0.15 * powf(x, 2.) + 290.4);
		sfSprite_setPosition(window->player->sp, window->player_pos);
		if (window->ground != 756) {
			sfSprite_rotate(window->player->sp, -3);
		}
		if (PLAYER_Y > 1300) {
			window->menu = END_MENU;
		}
	}
}

void read_buffer(char *buf, my_w_t *window)
{
	for (int i = 0; i < 512; i++, window->map_length++) {
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
	while (window->map_length % 512 == 0) {
		read(fd, buf, 512);
		read_buffer(buf, window);
	}
	close(fd);
	fd = open(str, O_RDONLY);
	for (int i = 0; i < 12; i++) {
		window->map[i] = malloc(sizeof(char)
		* (window->map_length + 1));
		if (!window->map[i])
			return (84);
		read(fd, window->map[i], window->map_length + 1);
		window->map[i][window->map_length] = 0;
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
	sfTexture_destroy(tmp->tx);
	free(tmp);
}

void clear_my_game_objs_from_desired(my_w_t *window, my_obj_type_t type)
{
	game_objs_t *tmp = window->first;

	while (tmp) {
		if (tmp->type == type)
			destroy_obj_and_relink(window, tmp);
		tmp = tmp->next;
	}
}

void restart_game(my_w_t *window)
{
	set_my_map_states_to_default(window);
	set_my_player_states_and_jump_to_default(window);
	sfSprite_setPosition(window->player->sp, window->player_pos);
	sfSprite_setRotation(window->player->sp, 0);
	clear_my_game_objs_from_desired(window, BOX);
	clear_my_game_objs_from_desired(window, SPIKE);
}

void check_menu_type_for_action(my_w_t *window)
{
	if (window->menu != MAIN_MENU)
		restart_game(window);
	window->menu = NONE_MENU;
}

void select_choice(my_w_t *window, int *selected)
{
	if (sfKeyboard_isKeyPressed(sfKeyReturn) == sfTrue) {
		switch (*selected) {
			case 1:
			check_menu_type_for_action(window);
			break;
			case 2:
			window->end_game = sfTrue;
			break;
		}
	}
	if (sfKeyboard_isKeyPressed(sfKeyUp) == sfTrue) {
		*selected = 1;
		sfMusic_play(window->select_sound);
	} else if (sfKeyboard_isKeyPressed(sfKeyDown) == sfTrue) {
		*selected = 2;
		sfMusic_play(window->select_sound);
	}
}

void display_menu_type(my_w_t *window, my_obj_type_t menu_type)
{
	game_objs_t *tmp = window->first;
	static sfVector2f selector_pos_up = {545, 125};
	static sfVector2f selector_pos_down = {545, 595};
	static int selected = 1;

	while (tmp) {
		if (tmp->type == menu_type)
			sfRenderWindow_drawSprite(window->window,
				tmp->sp, NULL);
		tmp = tmp->next;
	}
	if (selected == 1) {
		sfSprite_setPosition(window->selector->sp, selector_pos_up);
	} else if (selected == 2)
		sfSprite_setPosition(window->selector->sp, selector_pos_down);
	sfRenderWindow_drawSprite(window->window, window->selector->sp, NULL);
	select_choice(window, &selected);
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
	}
	return (0);
}

void free_music(my_w_t *window)
{
	sfMusic_destroy(window->select_sound);
	sfMusic_destroy(window->jump_sound);
	sfMusic_destroy(window->death_sound);
	sfMusic_destroy(window->game_music);
	sfMusic_destroy(window->win_music);
	sfMusic_destroy(window->lose_music);
}

void destroy_and_free(my_w_t *window)
{
	game_objs_t *tmp;

	while (window->first) {
		tmp = window->first;
		window->first = window->first->next;
		sfSprite_destroy(tmp->sp);
		sfTexture_destroy(tmp->tx);
		free(tmp);
	}
	free_music(window);
	for (int i = 0; i < 12; i++)
		free(window->map[i]);
	free(window->map);
	sfRenderWindow_destroy(window->window);
}

int main(int ac, char **av)
{
	my_w_t window = init_my_window();

	if (!window.first || window.error_no != 0 || ac != 2
		|| create_and_load(av[1], &window) != 0) {
		print_my_helper();
		return (84);
	}
	sfMusic_play(window.game_music);
	sfMusic_setLoop(window.game_music, sfTrue);
	sfRenderWindow_setFramerateLimit(window.window, 120);
	while (sfRenderWindow_isOpen(window.window)) {
		get_time(&window.clocker);
		if (window.end_game == sfTrue)
			sfRenderWindow_close(window.window);
		if (display_lobby(&window) != 0)
			return (84);
		analyse_events(&window);
	}
	destroy_and_free(&window);
	return (0);
}
