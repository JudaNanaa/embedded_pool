# include <avr/io.h>       // AVR I/O register definitions
# include <util/delay.h>   // Library for delay functions
# include <stdbool.h>      // For using boolean values

# define ALL_OPEN 23       // All LEDs ON (PB0, PB1, PB2, PB4)
# define NOTHING_OPEN 0    // All LEDs OFF

# define BOUNCE_MS 20      // Debounce time in milliseconds

// Function to change LED state based on the increment
void change_led(int increment) {
	PORTB += increment; // Adjust LED states

	// Special case handling for transition between PB2 and PB4
	if (PORTB == 8 && increment == 1) { 
		PORTB = 16; // Open PB4 directly
	}
	else if (PORTB == 16 && increment == -1) {
		PORTB = 8; // Return to PB2, PB1, PB0 state
	}
}

// Function to manage button debounce effect
void bounce_effect(int button) {
	// Wait while the button is pressed to prevent bouncing
	while ((PIND & (1 << button)) == 0) { 
		_delay_ms(BOUNCE_MS);
	}
}

int main(void) 
{
	// Set PB0, PB1, PB2, and PB4 as output
	DDRB |= (1 << PB0) | (1 << PB1) | (1 << PB2) | (1 << PB4);

	while (true) {

		// Check if button SW1 (PD2) is pressed and LEDs are not fully ON
		if ((PIND & (1 << PD2)) == 0 && PORTB != ALL_OPEN) { 
			change_led(1); // Increment LED state
			bounce_effect(PD2); // Apply debounce
		}

		// Check if button SW2 (PD4) is pressed and LEDs are not fully OFF
		if ((PIND & (1 << PD4)) == 0 && PORTB != NOTHING_OPEN) { 
			change_led(-1); // Decrement LED state
			bounce_effect(PD4); // Apply debounce
		}
	}
	return (0); // End of program (not really needed for embedded systems)
}
