/*
** EPITECH PROJECT, 2017
** my_screensaver_2017
** File description:
** (main.c bootstrap runner)
*/
#include "include/my.h"

void move_rect(game_objs_t *rect)
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
	sfSprite_setPosition(obj->sp, *coords);
}

void create_spike(game_objs_t *obj, sfVector2f *coords)
{
	sfSprite_setPosition(obj->sp, *coords);
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
	}
}

game_objs_t *init_game_objs(const char *path_to_spritesheet, my_type_t type,
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

int add_to_list(const char *path_to_spritesheet, my_type_t type,
	my_w_t *window, sfVector2f coords)
{
	game_objs_t *new_obj = init_game_objs(path_to_spritesheet,
		type, &coords);

	if (new_obj == NULL)
		return (84);
	new_obj->next = window->first;
	if (new_obj->type == PLAYER)
		window->player = new_obj;
	if (new_obj->next != NULL)
		new_obj->next->prev = new_obj;
	window->first = new_obj;
	return (0);
}

void init_my_game_objects_list(my_w_t *window)
{
	window->error_no += add_to_list("textures/runner.png",
	(my_type_t)PLAYER, window, (sfVector2f){288, 756});
	window->error_no += add_to_list("textures/ground.png",
	(my_type_t)BACKGROUND, window, (sfVector2f){0, 0});
	window->error_no += add_to_list("textures/forest.png",
	(my_type_t)BACKGROUND, window, (sfVector2f){0, 0});
	window->error_no += add_to_list("textures/city1.png",
	(my_type_t)BACKGROUND, window, (sfVector2f){0, 0});
	window->error_no += add_to_list("textures/sky.png",
	(my_type_t)BACKGROUND, window, (sfVector2f){0, 0});
}

my_w_t init_my_window(void)
{
	my_w_t window;

	window.error_no = 0;
	window.jump_state = 0;
	window.map_length = 0;
	window.player_pos = (sfVector2f){288, 756};
	window.window = sfRenderWindow_create((sfVideoMode){1920, 1080, 32},
	"Bootstrap.Runner", sfFullscreen, NULL);
	window.clocker = init_timer();
	window.first = NULL;
	window.map = malloc(sizeof(char *) * 12);
	if (!window.window || !window.map)
		window.error_no = 84;
	init_my_game_objects_list(&window);
	return (window);
}

void analyse_events(my_w_t *window)
{
	while (sfRenderWindow_pollEvent(window->window, &window->event)) {
		if (window->event.type == sfEvtClosed
			|| sfKeyboard_isKeyPressed(sfKeyEscape) == sfTrue)
			sfRenderWindow_close(window->window);
		if (sfKeyboard_isKeyPressed(sfKeySpace) == sfTrue) {
			window->jump_state = 1;
			sfClock_restart(window->clocker.clock);
		}
	}
}

void move_those_amazing_rect(game_objs_t *tmp, my_w_t *window)
{
	if (tmp->type == PLAYER && window->clocker.seconds >= 0.085
		&& window->jump_state == 0) {
		move_rect(tmp);
		sfClock_restart(window->clocker.clock);
	}
	if (tmp->type == BACKGROUND)
		move_rect(tmp);
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

void display_obstacles(my_w_t *window)
{
	game_objs_t *tmp = window->first;
	sfVector2f pos = {0, 0};
	static int loader = 0;

	while (tmp) {
		if (tmp->type == SPIKE || tmp->type == BOX) {
			sfRenderWindow_drawSprite(window->window, tmp->sp, NULL);
			sfSprite_move(tmp->sp, (sfVector2f){-5, 0});
			pos = sfSprite_getPosition(tmp->sp);
			check_if_out_of_map(&pos, tmp);
		}
		tmp = tmp->next;
	}
	loader++;
}

void read_list_and_display(my_w_t *window)
{
	game_objs_t *tmp = window->first;

	while (tmp) {
		if (tmp->type != BACKGROUND && tmp->type != PLAYER) {
			tmp = tmp->next;
			continue;
		}
		move_those_amazing_rect(tmp, window);
		sfSprite_setTextureRect(tmp->sp, tmp->rect);
		sfRenderWindow_drawSprite(window->window, tmp->sp, NULL);
		tmp = tmp->next;
	}
	display_obstacles(window);
}

int get_x_pos(my_w_t *window)
{
	static int x = -44;

	if (x < 44) {
		x++;
	} else {
		window->jump_state = 0;
		x = -44;
	}
	return (x);
}

void jump_baby_jump(my_w_t *window)
{
	if (window->jump_state == 1) {
		window->player_pos.y = 756 -
		(-0.1 * powf(get_x_pos(window), 2) + 200);
		sfSprite_setPosition(window->player->sp, window->player_pos);
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

int seek_objs_first_time(my_w_t *window, int i)
{
	int error_no = 0;

	for (int j = 1; j < 21; j++) {
		if (window->map[i][j] == 'S') {
			error_no = add_to_list("textures/spike.png",
			(my_type_t)SPIKE, window,
			(sfVector2f){(j - 1) * 96, (i - 1) * 108});
		} else if (window->map[i][j] == 'O') {
			error_no = add_to_list("textures/box.png",
			(my_type_t)BOX, window,
			(sfVector2f){(j - 1) * 96, (i - 1) * 108});
		}
		if (error_no != 0)
			return (error_no);
	}
	return (0);
}

int load_first_part_map(my_w_t *window)
{
	for (int i = 1; i < 11; i++) {
		if (seek_objs_first_time(window, i) != 0)
			return (84);
	}
	return (0);
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
		window->map[i] = malloc(sizeof(char) * (window->map_length + 1));
		if (!window->map[i])
			return (84);
		read(fd, window->map[i], window->map_length + 1);
		window->map[i][window->map_length] = 0;
	}
	return (load_first_part_map(window));
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

int main(int ac, char **av)
{
	my_w_t window = init_my_window();

	if (window.first == NULL || window.error_no != 0
		|| ac != 2 || create_and_load(av[1], &window) != 0) {
		print_my_helper();
		return (84);
	}
	while (sfRenderWindow_isOpen(window.window)) {
		get_time(&window.clocker);
		if (fmodf(window.clocker.seconds, 1.0/60.0) >= 0 &&
		fmodf(window.clocker.seconds, 1.0/60.0) < 0.01) {
			sfRenderWindow_clear(window.window, sfBlack);
			jump_baby_jump(&window);
			read_list_and_display(&window);
			sfRenderWindow_display(window.window);
		}
		analyse_events(&window);
	}
	return (0);
}
