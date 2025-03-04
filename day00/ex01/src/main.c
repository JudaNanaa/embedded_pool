#include <avr/io.h>



int main()
{
    DDRB |= (1 << PB0);    // Set PB0 as output (LED control)

    PORTB = 0x1; // Turn ON LED (PB0)

	while (1) {
		continue;
	}
    return 0;
}