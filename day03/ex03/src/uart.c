#include "../includes/includes.h"
#include <stdint.h>

void uart_init() {
    UBRR0H = BAUD_PRESCALER >> 8;
    UBRR0L = BAUD_PRESCALER;

    BIT_SET(UCSR0B, TXEN0);
    BIT_SET(UCSR0B, RXEN0);

    BIT_SET(UCSR0C, UCSZ01);
    BIT_SET(UCSR0C, UCSZ00);
}

void uart_tx(char c) {
    while ((UCSR0A & (1 << UDRE0)) == 0);
    UDR0 = c;
}

char uart_rx(void) {
    while (IS_LOW(UCSR0A, RXC0));
    return UDR0;
}

void	uart_putnbr(int64_t n)
{
	int64_t	nb;
	char	c;

	nb = n;
	if (nb < 0)
	{
		nb = -nb;
		uart_tx('-');
	}
	if (nb >= 10)
	{
		uart_putnbr(nb / 10);
		uart_putnbr(nb % 10);
	}
	if (nb < 10)
	{
		c = nb + '0';
		uart_tx(c);
	}
}

void uart_printstr(const char* str) {
    while (*str) {
        uart_tx(*str++);
    }
}