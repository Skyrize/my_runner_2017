/*
** EPITECH PROJECT, 2017
** my_runner_2017
** File description:
** (enter)
*/
#include "include/my.h"

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
	if (MAP_T.map_reader >= MAP_T.map_length) {
		my_printf("\nYou Won !\n\n");
		sfRenderWindow_close(window->window);
	}
	MAP_T.map_reader++;
	return (0);
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
