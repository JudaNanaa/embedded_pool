#include "../includes/includes.h"
#include <stdbool.h>
#include <stdint.h>

void turnRed() {
	BIT_SET(PORTD, PD5);
}

void turnGreen() {
	BIT_SET(PORTD, PD6);
}

void turnBlue() {
	BIT_SET(PORTD, PD3);
}

void color(uint8_t red, uint8_t green, uint8_t blue) {
	CLEAR(PORTD);
	if (red) {
		turnRed();		
	}
	if (green) {
		turnGreen();
	}
	if (blue) {
		turnBlue();
	}
	_delay_ms(1000);
}

void init_rgb();

void set_rgb(uint8_t r, uint8_t g, uint8_t b) {
	
}

void wheel(uint8_t pos) {
	pos = 255 - pos;
	if (pos < 85) {
		set_rgb(255 - pos * 3, 0, pos * 3);
	} else if (pos < 170) {
		pos = pos - 85;
		set_rgb(0, pos * 3, 255 - pos * 3);
	} else {
		pos = pos - 170;
		set_rgb(pos * 3, 255 - pos * 3, 0);
	}
}

int main(void) {
	BIT_SET(DDRD, PD3);
	BIT_SET(DDRD, PD5);
	BIT_SET(DDRD, PD6);

    while (true) {
		uint8_t pos = 0;
		while (pos <= 255) {
			wheel(pos);
			_delay_ms(7000 / 255);
			pos++;
		}
		while 
    }
    return 0;
}
