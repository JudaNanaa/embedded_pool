#include <avr/io.h>
#include <stdbool.h>

#define BIT_CLEAR(reg, bit) (reg &= ~(1 << bit))
#define BIT_SET(reg, bit) (reg |= (1 << bit))

void setup() {
	BIT_SET(DDRB, PB1);
    
    TCCR1A = 0;
	OCR1A = 6553;
	ICR1 = 65535;

	BIT_SET(TCCR1A, COM1A1);
	BIT_CLEAR(TCCR1A, COM1A0);

	// fast pwm : 14
    BIT_CLEAR(TCCR1A, WGM10);
    BIT_SET(TCCR1A, WGM11);

    BIT_SET(TCCR1B, WGM12);
    BIT_SET(TCCR1B, WGM13);

	// prescaller
	BIT_CLEAR(TCCR1B, CS10);
	BIT_CLEAR(TCCR1B, CS11);
	BIT_SET(TCCR1B, CS12);
}

int main(void) {
    setup();
    
    while (true) {
    }
    
    return 0;
}
