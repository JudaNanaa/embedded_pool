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
	while (IS_LOW(UCSR0A, UDRE0));

    UDR0 = c;
}

char uart_rx(void) {
	/* Wait for data to be received */
	while (IS_LOW(UCSR0A, RXC0));
	/* Get and return received data from buffer */
	return UDR0;
}

int main(void) {
	char c;

	uart_init();
	while (1) {
		c = uart_rx();
		uart_tx(c);
	}
    return 0;
}
