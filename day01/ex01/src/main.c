#include <avr/io.h>
#include <stdbool.h>

#define BIT_CLEAR(reg, bit) (reg &= ~(1 << bit))
#define BIT_SET(reg, bit) (reg |= (1 << bit))

void setup() {
    DDRB |= (1 << PB1);
    
    TCCR1A = 0;
    BIT_SET(TCCR1A, COM1A0);
    BIT_CLEAR(TCCR1A, COM1A1);

	// fast PWM : 14
    BIT_CLEAR(TCCR1A, WGM10);
    BIT_SET(TCCR1A, WGM11);
    BIT_SET(TCCR1B, WGM12);
    BIT_SET(TCCR1B, WGM13);

    BIT_SET(TCCR1B, CS12);
    BIT_CLEAR(TCCR1B, CS11);
    BIT_CLEAR(TCCR1B, CS10);

    OCR1A = 31250;

    TCNT1 = 0;
}

int main(void) {
    setup();
    
    while (true) {
    }
    
    return 0;
}
