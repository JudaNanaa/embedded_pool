#ifndef INCLUDES_H
#define INCLUDES_H

#include <util/twi.h>
#include <stdint.h>
#include <util/delay.h>
#include <avr/io.h>

#define BAUD_PRESCALER ((F_CPU / (16UL * BAUDRATE)))

#define BOUNCE_MS 20  // Debounce time in milliseconds

#define IS_LOW(pin, button) ((pin & (1 << button)) == 0)
#define BIT_CLEAR(reg, bit) (reg &= ~(1 << bit))
#define BIT_SET(reg, bit) (reg |= (1 << bit))
#define CLEAR(reg) (reg = 0)

#define MAX 65535
#define STEP (MAX / 10)  // Change by 10% per step

#define TWI_FREQ 100000L

void uart_init();
void uart_tx(char c);
char uart_rx(void);
void uart_printstr(const char* str);

#endif