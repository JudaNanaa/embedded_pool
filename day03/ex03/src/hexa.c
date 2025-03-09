#include "../includes/includes.h"
#include <stdint.h>

#define COLOR_TOO_LONG "\r\nCOLOR can be max 100 characters!\r\n"
#define COLOR_ERROR "\r\nCOLOR error\r\n"

int index_in_base(char c, const char *charset) {
    for (int i = 0; charset[i]; i++) {
        if (charset[i] == c)
            return i;
    }
    return -1;  // Return -1 to indicate an invalid character
}

bool is_in_charset(char c, const char *charset) {
    return index_in_base(c, charset) != -1;
}

int64_t ft_atoi_base(char *str, int len) {
    int64_t result = 0;
    int64_t i = 0;

    while (i < len) {
        result *= 16;
        
        int index = index_in_base(str[i], CHARSET_LOW);
        if (index == -1)
            index = index_in_base(str[i], CHARSET_HIGH);
        
        result += index;
        i++;
    }
    return result;
}

int get_prompt(char *buff) {
	int i = 0;
	char c;

	while (i < 100) {
		c = uart_rx();
        if (c == ENTER) {
            buff[i] = '\0';
            uart_printstr("\r\n");
            return 0;
        }
		if (c == BACKSPACE) {
            if (i > 0) {
                i--;
                uart_printstr("\b \b");
            }
        }
		else {
            buff[i++] = c;
            uart_tx(c);
        }
	}
    uart_printstr(COLOR_TOO_LONG);
	return -1;
}

bool is_well_formated(char *buff) {
	if (ft_strlen(buff) != 7) {
		return false;
	}
	if (buff[0] != '#') {
		return false;
	}
	for (int i = 1; buff[i]; i++) {
		if (is_in_charset(buff[i], CHARSET) == false) {
			return false;
		}
	}
	return true;
}

void get_hexa(t_rgb *color) {
	char buff[100];

	while (true) {
		uart_printstr("Color> ");
		if (get_prompt(buff) == -1) {
			continue;
		}
		if (is_well_formated(buff) == false) {
			uart_printstr(COLOR_ERROR);
			continue;
		}
		break;
	}
	color->red = ft_atoi_base(&buff[1], 2);
	color->green = ft_atoi_base(&buff[3], 2);
	color->blue = ft_atoi_base(&buff[5], 2);
}