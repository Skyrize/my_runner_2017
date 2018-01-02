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

typedef struct my_window_s
{
	int error_no;
	int ground;
	int jump_x;
	int jump_stock;
	sfBool jump_state;
	sfBool on_box;
	unsigned int map_length;
	char **map;
	sfVector2f player_base_pos;
	sfVector2f player_pos;
	sfRenderWindow *window;
	sfEvent event;
	sfMusic *music;
	ctime_t clocker;
	game_objs_t *first;
	game_objs_t *player;
} my_w_t;

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

ctime_t init_timer(void);
my_w_t init_my_window(void);
void destroy_and_free(my_w_t *);
void get_time(ctime_t *);
void analyse_events(my_w_t *);

#define BASE window->player_base_pos
#define PLAYER_Y window->player_pos.y
#define OBJ_Y obj_pos->y
#define OBJ_X obj_pos->x
#endif /* MY_H_ */
