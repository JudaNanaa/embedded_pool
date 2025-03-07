#ifndef INCLUDES_H
#define INCLUDES_H

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdbool.h>

#define BOUNCE_MS 20  // Debounce time in milliseconds

#define IS_LOW(pin, button) ((pin & (1 << button)) == 0)
#define BIT_CLEAR(reg, bit) (reg &= ~(1 << bit))
#define BIT_SET(reg, bit) (reg |= (1 << bit))
#define CLEAR(reg) (reg = 0)

#define MAX 65535
#define STEP (MAX / 10)  // Change by 10% per step

#endif