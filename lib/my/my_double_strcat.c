/*
** EPITECH PROJECT, 2017
** PSU_my_ls_2017
** File description:
** (concat 2 string into a created third)
*/
#include <stdlib.h>

int my_strlen(char *);
char *my_double_strcat(char *str1, char *str2)
{
	char *str = malloc(sizeof(char) * (my_strlen(str1)
	+ my_strlen(str2) + 2));
	int i = 0;
	int j = 0;

	if (str == NULL) {
		return (NULL);
	}
	while (str1 && str1[i]) {
		str[i] = str1[i];
		i++;
	}
	str[i] = '/';
	while (str2 && str2[j]) {
		str[i + 1 + j] = str2[j];
		j++;
	}
	str[i + j + 1] = 0;
	return (str);
}
