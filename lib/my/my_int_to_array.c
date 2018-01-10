/*
** EPITECH PROJECT, 2017
** my_runner_2017
** File description:
** (enter)
*/
#include "../../include/my.h"

void return_number_size(int *nb, int *neg, int *length, int *between_1)
{
	int between_2 = 10;

	if (*nb < 0) {
		*neg = 1;
		*nb = -(*nb);
		*length = 2;
	}
	while (1) {
		if (*nb >= *between_1 && *nb < between_2) {
			break;
		} else {
			(*length)++;
			*between_1 *= 10;
			between_2 *= 10;
		}
	}
}

void fill_str(int nb, int length, int between_1, char *str)
{
	int neg = 0;

	if (str[0] == '-')
		neg = 1;
	for (int i = neg; i < length; i++) {
		if (nb > 0) {
			str[i] = nb / between_1 + '0';
			nb = nb % between_1;
			between_1 = between_1 / 10;
		} else
			str[i] = nb + '0';
	}
}

char *my_int_to_array(int nb)
{
	char *str = "0";
	int neg = 0;
	int length = 1;
	int between_1 = 1;

	if (nb == 0)
		return (str);
	return_number_size(&nb, &neg, &length, &between_1);
	str = malloc(sizeof(char) * (length + 1));
	if (neg == 1)
		str[0] = '-';
	str[length] = 0;
	fill_str(nb, length, between_1, str);
	return (str);
}
