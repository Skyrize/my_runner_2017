/*
** EPITECH PROJECT, 2017
** my.h
** File description:
** all prototypes
*/

#ifndef MY_H_
#define MY_H_
#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <SFML/Window.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
void my_putchar(char);
int my_isneg(int);
int my_put_nbr(int);
void my_put_ull(unsigned long long);
void my_put_llnbr(long long int);
void my_putnbr_base(unsigned long long, char *);
int my_swap(int *, int *);
int my_putstr(char const *);
int my_strlen(char const *);
int my_getnbr(char const *);
void my_sort_int_array(int *, int);
int my_compute_power_rec(int, int);
int my_compute_square_root(int);
int my_is_prime(int);
int my_find_prime_sup(int);
char *my_strcpy(char *, char const *);
char *my_strncpy(char *, char const *, int);
char *my_revstr(char *);
char *my_strstr(char const *, char const *);
int my_strcmp(char const *, char const *);
int my_strncmp(char const *, char const *, int);
char *my_strupcase(char *);
char *my_strlowcase(char *);
char *my_strcapitalize(char *);
int my_str_isalpha(char const *);
int my_str_isnum(char const *);
int my_str_islower(char const *);
int my_str_isupper(char const *);
int my_str_isprintable(char const *);
int my_showstr(char const *);
int my_showmem(char const *, int);
char *my_strcat(char *, char const *);
char *my_strncat(char *, char const *, int);
char *my_int_to_array(int);

/* MY_PRINTF */

int my_printf(char *, ...);
void my_printunsignedint(va_list);
void my_printchar(va_list);
void my_printint(va_list);
void my_printstr(va_list);
void my_printlowhexa(va_list);
void my_printuphexa(va_list);
void my_printbinary(va_list);
void my_printadress(va_list);
void my_printoctal(va_list);
void my_printpercent(va_list);
void my_printformatedstring(va_list);

typedef struct fnct_s
{
	char balise;
	void (*fptr)(va_list list);
} fnct_t;

/* CSFML */

typedef struct framebuffer_s
{
	unsigned int width;
	unsigned int height;
	sfUint8 *pixels;
} framebuffer_t;

void place_a_square(sfVector2f *, sfVector2f *, sfRenderWindow *, sfColor *);

/* MY_RUNNER */

typedef struct ctime_s
{
	sfClock *clock;
	sfTime timer;
	float seconds;
} ctime_t;

typedef struct game_objs_s game_objs_t;

typedef enum
{
	NONE_MENU,
	MAIN_MENU,
	PAUSE_MENU,
	END_MENU,
} my_menu_type_t;

typedef struct textures_lib_s
{
	sfTexture *player_tx;
	sfTexture *spike_tx;
	sfTexture *box_tx;
	sfTexture *ground_tx;
	sfTexture *forest_tx;
	sfTexture *city1_tx;
	sfTexture *sky_tx;
	sfTexture *switch_on_off_tx;
	sfTexture *selector_tx;
	sfTexture *win_menu_tx;
	sfTexture *main_menu_tx;
	sfTexture *pause_exit_tx;
} textures_lib_t;

typedef struct audio_lib_s
{
	sfMusic *select_sound;
	sfMusic *jump_sound;
	sfMusic *death_sound;
	sfMusic *game_music;
	sfMusic *lose_music;
	sfMusic *win_music;
} audio_lib_t;

typedef struct map_tools_s
{
	unsigned int map_loader;
	unsigned int map_reader;
	unsigned int map_length;
	char **map;
} map_tools_t;

typedef struct game_tools_s
{
	int ground;
	int jump_x;
	int jump_max;
	int obj_start_offset;
	sfBool infinite_mode;
	sfBool end_game;
	sfBool jump_state;
	sfBool on_box;
	sfVector2f player_pos;
	sfVector2f player_base_pos;
} game_tools_t;

typedef struct score_tools_s
{
	unsigned int score_points;
	sfFont *font;
	sfText *score;
	sfText *points;
} score_tools_t;

typedef struct my_window_s
{
	int error_no;
	sfRenderWindow *window;
	sfEvent event;
	ctime_t clocker;
	score_tools_t score_tools;
	game_tools_t game_tools;
	map_tools_t map_tools;
	my_menu_type_t menu;
	textures_lib_t txtrs_lib;
	audio_lib_t audio_lib;
	game_objs_t *first;
	game_objs_t *switcher;
	game_objs_t *selector;
	game_objs_t *player;
} my_w_t;

typedef enum
{
	PLAYER,
	BACKGROUND,
	BOX,
	SPIKE,
	MAIN,
	PAUSE,
	END,
	MENU_SELECTOR,
} my_obj_type_t;

typedef struct game_objs_s
{
	my_obj_type_t type;
	sfSprite *sp;
	sfIntRect rect;
	int rect_max_value;
	int rect_offset;
	game_objs_t *next;
	game_objs_t *prev;
} game_objs_t;

ctime_t init_timer(void);
my_w_t init_my_window(void);
void destroy_and_free(my_w_t *);
void get_time(ctime_t *);
void analyse_events(my_w_t *);
int choose_my_menu_or_game(my_w_t *);
void destroy_musics(my_w_t *window);
void destroy_my_textures_lib(my_w_t *window);
void destroy_and_free_my_objs(my_w_t *window);
void free_my_map(my_w_t *window);
void destroy_my_score(my_w_t *window);
int create_and_load(char *str, my_w_t *window);
void check_menu_type_for_action(my_w_t *window);
void display_menu_type(my_w_t *window, my_obj_type_t menu_type);
void restart_game(my_w_t *window);
void select_choice(my_w_t *window, int *selected, my_obj_type_t *menu_type);
int compute_and_display_game(my_w_t *window);
int accelerate_my_game(my_w_t *window);
int add_to_list(sfTexture *texture, my_obj_type_t type, my_w_t *window, sfVector2f coords);
void check_if_out_of_map(sfVector2f *pos, game_objs_t *obj);
int load_one_more_line(my_w_t *window);
void kill_my_budy(my_w_t *window);
void move_those_amazing_rect(game_objs_t *tmp, my_w_t *window);
void create_player(game_objs_t *obj, sfVector2f *coords);
void create_background(game_objs_t *obj);
void create_box(game_objs_t *obj, sfVector2f *coords, my_w_t *);
void create_spike(game_objs_t *obj, sfVector2f *coords, my_w_t *);
void create_menu(game_objs_t *obj, sfVector2f *coords);
void create_menu_selector(game_objs_t *obj, sfVector2f *coords);
void set_my_game_tools_to_default(my_w_t *window);
void set_my_map_tools_to_default(my_w_t *window, sfBool init);
void set_my_score_to_zero(my_w_t *window);
void init_my_game_objects_list(my_w_t *window);
int display_obstacles(my_w_t *window);
void display_player(my_w_t *window);
void jump_baby_jump(my_w_t *window);

#define SCORE_T window->score_tools
#define GAME_T window->game_tools
#define MAP_T window->map_tools
#define AUDIO_L window->audio_lib
#define TXTR_L window->txtrs_lib
#define BASE GAME_T.player_base_pos
#define PLAYER_X GAME_T.player_pos.x
#define PLAYER_Y GAME_T.player_pos.y
#define OBJ_Y obj_pos->y
#define OBJ_X obj_pos->x
#endif /* MY_H_ */
