#include "../includes/includes.h"
#include <stdbool.h>
#include <stdint.h>

void turnRed() {
	CLEAR(PORTD);
	BIT_SET(PORTD, PD5);
	_delay_ms(1000);
}

void turnGreen() {
	CLEAR(PORTD);
	BIT_SET(PORTD, PD6);
	_delay_ms(1000);
}

void turnBlue() {
	CLEAR(PORTD);
	BIT_SET(PORTD, PD3);
	_delay_ms(1000);
}



int main(void) {
	BIT_SET(DDRD, PD3);
	BIT_SET(DDRD, PD5);
	BIT_SET(DDRD, PD6);

    while (true) {
		turnRed();
		turnGreen();
		turnBlue();
    }
    return 0;
}
