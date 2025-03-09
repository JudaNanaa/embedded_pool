#include "../includes/includes.h"
#include <stdbool.h>

int ft_strlen(char *str) {
	int i = 0;

	while (str[i])
		i++;
	return i;
}

// bool is_in_charset(char c, char *charset) {
// 	int i = 0;

// 	while (charset[i]) {
// 		if (charset[i] == c) {
// 			return true;
// 		}
// 		i++;
// 	}
// 	return false;
// }
