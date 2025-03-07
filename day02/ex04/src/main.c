#include "../includes/includes.h"
#include <stdbool.h>
#include <stdint.h>

#define BAUD_PRESCALER ((F_CPU / (16UL * BAUDRATE)))

#define ENTER_LOGIN "Enter your login:\r\n"
#define USERNAME "Moussa"
#define PASSWORD "test"
#define ENTER_USERNAME "	username: "
#define ENTER_PASSWORD "	password: "
#define ENTER 13
#define BACKSPACE 127
#define USERNAME_TOO_LONG "\r\nUsername can be max 100 characters!\r\n"
#define PASSWORD_TOO_LONG "\r\nPassword can be max 100 characters!\r\n"
#define ACCESS_DENIED "Bad combination username/password\r\n\r\n"
#define ACCESS_GRANTED "\r\nHello Moussa!\r\n"
#define PLAY_GAME "Shall we play a game?\r\n"

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

void uart_printstr(const char* str) {
    while (*str) {
        uart_tx(*str++);
    }
}

int get_prompt(char *buff, bool echo ,const char *message_on_error) {
    int i = 0;
    char c;

    while (i < 100) {
        c = uart_rx();
        if (c == ENTER) {
            buff[i] = '\0';
            uart_printstr("\r\n");
            return 0;
        }
        if (c == BACKSPACE) {
            if (i > 0) {
                i--;
                uart_printstr("\b \b");
            }
        }
		else {
            buff[i++] = c;
			if (echo == true)
            	uart_tx(c);
			else
				uart_tx('*');
        }
    }
    uart_printstr(message_on_error);
    return -1;
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int			i;
	unsigned char	*true_s1;
	unsigned char	*true_s2;

	true_s1 = (unsigned char *)s1;
	true_s2 = (unsigned char *)s2;
	i = 0;
	while (true_s2[i] || true_s1[i])
	{
		if (true_s1[i] != true_s2[i])
		{
			if (true_s1[i] < true_s2[i])
				return (-1);
			return (1);
		}
		i++;
	}
	return (0);
}

void turn_light_succes() {
	BIT_SET(DDRD, PD6);

	BIT_SET(PORTD, PD6);
}

void turn_light_error() {
	BIT_SET(DDRD, PD5);

	BIT_SET(PORTD, PD5);
}

void login() {
    char buffer_username[100];
    char buffer_password[100];

    while (true) {
		uart_printstr(ENTER_LOGIN);
        uart_printstr(ENTER_USERNAME);
		if (get_prompt(buffer_username, true, USERNAME_TOO_LONG) == -1) {
            continue;
        }

        uart_printstr(ENTER_PASSWORD);
        if (get_prompt(buffer_password, false, PASSWORD_TOO_LONG) == -1)  {
            continue;
        }

        if (ft_strcmp(buffer_username, USERNAME) == 0 && ft_strcmp(buffer_password, PASSWORD) == 0) {
            uart_printstr(ACCESS_GRANTED);
			turn_light_succes();
            return;
        } else {
			_delay_ms(1000);
            uart_printstr(ACCESS_DENIED);
			turn_light_error();
        }
    }
}

int main(void) {
    uart_init();
    login();
	uart_printstr(PLAY_GAME);
    while (1) {
    }
    return 0;
}
