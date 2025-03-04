# include <avr/io.h>       // AVR I/O register definitions
# include <util/delay.h>   // Library for delay functions
# include <stdbool.h>      // For using boolean values

# define BOUNCE_MS 20 // Debounce time in milliseconds

int main(void) 
{
	DDRB = (1 << PB0); // Set PB0 as output (LED or any other output)

	while (true) {
		// Check if the button (connected to PD2) is pressed
		if (((PIND & (1 << PD2)) >> PD2) == 0) {
			PORTB = !(PORTB); // Toggle PB0 (LED ON/OFF)

			// Wait until the button is released (debounce mechanism)
			while (((PIND & (1 << PD2)) >> PD2) == 0) {
				_delay_ms(BOUNCE_MS);
			}
		}
	}
	return (0); // End of program (not really needed for embedded systems)
}
