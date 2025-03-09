#include "../includes/includes.h"
#include <stdint.h>

void init_rgb()
{
	BIT_SET(DDRD, PD3);
	BIT_SET(DDRD, PD5);
	BIT_SET(DDRD, PD6);

	CLEAR(TCCR2A);
	CLEAR(TCCR0A);

	BIT_SET(TCCR2A, COM2B1);
	BIT_CLEAR(TCCR2A, COM2B0);

	BIT_SET(TCCR0A, COM0B1);
	BIT_CLEAR(TCCR0A, COM0B0);

	BIT_SET(TCCR0A, COM0A1);
	BIT_CLEAR(TCCR0A, COM0A0);


	BIT_SET(TCCR2A, WGM20);
	BIT_SET(TCCR2A, WGM21);
	BIT_CLEAR(TCCR2B, WGM22);

	BIT_SET(TCCR0A, WGM00);
	BIT_SET(TCCR0A, WGM01);
	BIT_CLEAR(TCCR0B, WGM02);

	BIT_SET(TCCR0B, CS00);

	BIT_SET(TCCR2B, CS20);


	OCR0A = 0;
	OCR0B = 0;
	OCR2B = 0;
}

void set_rgb(uint8_t r, uint8_t g, uint8_t b)
{
	OCR0A = r;
	OCR0B = g;
	OCR2B = b;
}

void wheel(t_rgb color) {
    set_rgb(color.red, color.green, color.blue);
}

