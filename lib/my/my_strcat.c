/*
** EPITECH PROJECT, 2017
** my str cat
** File description:
** concatenates two strings
*/

char *my_strcat(char *dest, char const *src)
{
	int i = 0;
	int z = 0;

	while (dest[i] != 0)
		i++;
	while (src[z] != 0) {
		dest[i] = src[z];
		i++;
		z++;
	}
	return (dest);
}
