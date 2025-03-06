#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>

#define BOUNCE_MS 20  // Debounce time in milliseconds

#define IS_LOW(pin, button) ((pin & (1 << button)) == 0)
#define BIT_CLEAR(reg, bit) (reg &= ~(1 << bit))
#define BIT_SET(reg, bit) (reg |= (1 << bit))
#define CLEAR(reg) (reg = 0)

#define MAX 65535
#define STEP (MAX / 10)  // Change by 10% per step

uint16_t duty_cycle = MAX / 2;  // Start at 50%

void change_duty_cycle(int increment) {
    if (increment < 0 && duty_cycle > STEP) {
        duty_cycle -= STEP;
    } else if (increment > 0 && duty_cycle < MAX - STEP) {
        duty_cycle += STEP;
    }
    OCR1A = duty_cycle;
}

void setup() {
    BIT_SET(DDRB, PB1);  // Set PB1 (OC1A) as output

    TCCR1A = 0;
    OCR1A = duty_cycle;
    ICR1 = MAX;

    BIT_SET(TCCR1A, COM1A1);
    BIT_CLEAR(TCCR1A, COM1A0);

    // Fast PWM mode 14
    BIT_CLEAR(TCCR1A, WGM10);
    BIT_SET(TCCR1A, WGM11);
    BIT_SET(TCCR1B, WGM12);
    BIT_SET(TCCR1B, WGM13);

    // Prescaler: clk/256
    BIT_CLEAR(TCCR1B, CS10);
    BIT_CLEAR(TCCR1B, CS11);
    BIT_SET(TCCR1B, CS12);

    // Set PD2 and PD4 as input with pull-ups enabled
    BIT_CLEAR(DDRD, PD2);
    BIT_CLEAR(DDRD, PD4);
    BIT_SET(PORTD, PD2);
    BIT_SET(PORTD, PD4);
}

// Function to manage button debounce effect
void bounce_effect(int button) {
    while (IS_LOW(PIND, button)) {
        _delay_ms(BOUNCE_MS);
    }
}

int main(void) {
    setup();

    while (true) {
        if (IS_LOW(PIND, PD2)) {
            change_duty_cycle(1);
            bounce_effect(PD2);
        } else if (IS_LOW(PIND, PD4)) {
            change_duty_cycle(-1);
            bounce_effect(PD4);
        }
    }

    return 0;
}
