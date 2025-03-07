#include "../includes/includes.h"
#include <stdint.h>

#define BAUD_PRESCALER ((F_CPU / (16UL * BAUDRATE)))

void uart_init() {
	UBRR0H = BAUD_PRESCALER >> 8;
	UBRR0L = BAUD_PRESCALER;

	BIT_SET(UCSR0B, TXEN0);
	BIT_SET(UCSR0B, RXEN0);
	
	BIT_SET(UCSR0C, UCSZ01);
	BIT_SET(UCSR0C, UCSZ00);
}

void uart_tx(char c) {
    while((UCSR0A & (1 << UDRE0)) == 0);

    UDR0 = c;
}

void uart_printstr(const char* str) {
	int i;

	i = 0;
	while (str[i]) {
		uart_tx(str[i]);
		i++;
	}
}

void setup() {
	// prescaler 1024
	TCNT1 = 34286;
	BIT_SET(TCCR1B, CS12);
	BIT_CLEAR(TCCR1B, CS11);
	BIT_SET(TCCR1B, CS10);

	BIT_SET(TIMSK1, TOIE1);
	sei();
}

ISR(TIMER1_OVF_vect) {
	TCNT1 = 34286;
	uart_printstr("Hello World!\r\n");
}

int main(void) {
	uart_init();
	setup();
	while (1) {
	}
    return 0;
}
