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

void setup() {
	BIT_SET(UCSR0B, RXCIE0);
	sei();
}

void UppercaseLowercase(char c) {
	if (c >= 'a' && c <= 'z') {
		c -= 32;
	}
	else if (c >= 'A' && c <= 'Z') {
		c += 32;
	}
	uart_tx(c);
}

ISR(USART_RX_vect) {
	UppercaseLowercase(UDR0);
}

int main(void) {
	uart_init();
	setup();
	while (1) {
	}
    return 0;
}
