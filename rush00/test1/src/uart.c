#include "../includes/includes.h"

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

void uart_printstr(const char* str) {
	int i;

	i = 0;
	while (str[i]) {
		uart_tx(str[i]);
		i++;
	}
}

