#ifndef INCLUDES_H
#define INCLUDES_H

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <stdint.h>

#define BOUNCE_MS 20  // Debounce time in milliseconds

#define IS_LOW(pin, button) ((pin & (1 << button)) == 0)
#define BIT_CLEAR(reg, bit) (reg &= ~(1 << bit))
#define BIT_SET(reg, bit) (reg |= (1 << bit))
#define CLEAR(reg) (reg = 0)

#define ENTER 13
#define BACKSPACE 127
#define CHARSET "0123456789abcdefABCDEF"
#define CHARSET_LOW "0123456789abcdef"
#define CHARSET_HIGH "0123456789ABCDEF"

#define BAUD_PRESCALER ((F_CPU / (16UL * BAUDRATE)))

typedef struct s_rgb{
	int64_t red;
	int64_t green;
	int64_t blue;
} t_rgb;

void init_rgb();

void get_hexa(t_rgb *color);

void wheel(t_rgb color);

// UART
void	uart_putnbr(int64_t n);
void uart_init();
char uart_rx(void);
void uart_tx(char c);
void uart_printstr(const char* str);

// Utils
int ft_strlen(char *str);
// bool is_in_charset(char c, char *charset);
#endif