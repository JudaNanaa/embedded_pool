#include "../includes/includes.h"
#include <stdbool.h>
#include <stdint.h>

int main(void) {
	t_rgb color;
	
	uart_init();
	init_rgb();
    while (true) {
		get_hexa(&color);
		wheel(color);
    }
    return 0;
}
