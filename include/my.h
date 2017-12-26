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
void my_amazing_sorter(int *, int);
void	rotate_left(int *, int, int *);
void	rotate_right(int *, int, int *);

typedef struct my_obj_s
{
	int state;
	sfSprite *sp;
	sfTexture *tx;
	sfVector2f speed;
	sfVector2f invert;
	sfVector2f position;
} objs_t;

typedef struct ctime_s
{
	sfClock *clock;
	sfTime timer;
	float seconds;
} ctime_t;

typedef struct fnct_s
{
	char balise;
	void (*fptr)(va_list list);
} fnct_t;

typedef struct point_s
{
	float x;
	float y;
} point_t;

typedef struct framebuffer_s
{
	unsigned int width;
	unsigned int height;
	sfUint8 *pixels;
} framebuffer_t;

typedef struct my_window_s my_w_t;

typedef struct graph_fnct_s
{
	int balise;
	int tab_length;
	sfColor color;
	objs_t *othtab;
	framebuffer_t *(*init_f)(void);
	void (*init_tab)(objs_t *, int, framebuffer_t *);
	void (*move_display)(my_w_t *, ctime_t *);
} graph_fnct_t;

typedef struct game_objs_s game_objs_t;

typedef struct my_window_s
{
	int error_no;
	int jump_state;
	unsigned int map_length;
	char **map;
	sfVector2f player_pos;
	sfRenderWindow *window;
	sfEvent event;
	ctime_t clocker;
	game_objs_t *first;
	game_objs_t *player;
} my_w_t;

ctime_t init_timer(void);
my_w_t init_my_window(void);
framebuffer_t *framebuffer_create(unsigned int, unsigned int);
sfMusic *init_music(void);
void displayer(my_w_t *, ctime_t *, int);
void destroy_and_free(my_w_t *, ctime_t *, int);
void gettime(ctime_t *);
void separate_operations(ctime_t *, my_w_t *, int);
void my_put_pixel(framebuffer_t *, unsigned int, unsigned int, sfColor);
framebuffer_t *draw_simple_squares(void);
void simple_squares_init(objs_t *, int, framebuffer_t *);
void opt_1_move_display(my_w_t *, ctime_t *);
void analyse_events(my_w_t *);
void analyse_events_opt1(my_w_t *, int);
void opt_2_move_display(my_w_t *, ctime_t *);
framebuffer_t *draw_simple_circles(void);
void simple_circles_init(objs_t *, int, framebuffer_t *);
void place_circles(objs_t *, int);
objs_t *init_my_othtab(void);
void look_for_balise(int, int, graph_fnct_t *, objs_t *);
void place_rounds(objs_t *, int);
void seconds_gesture(my_w_t *);

typedef enum
{
	PLAYER,
	BACKGROUND,
	BOX,
	SPIKE,
} my_type_t;

typedef struct game_objs_s
{
	my_type_t type;
	sfSprite *sp;
	sfTexture *tx;
	sfIntRect rect;
	int rect_max_value;
	int rect_offset;
	game_objs_t *next;
	game_objs_t *prev;
} game_objs_t;

#endif /* MY_H_ */
