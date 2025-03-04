# include <avr/io.h>     // AVR I/O register definitions
# include <stdbool.h>    // For using boolean values

int main(void) 
{
	DDRB = (1 << PB0); // Set PB0 as output (LED control)

	while (true) {
		// Check if the button (connected to PD2) is pressed
		if (((PIND & (1 << PD2)) >> PD2) == 0) {
			PORTB = 0x1; // Turn ON LED (PB0)
		}
		else {
			PORTB = 0x0; // Turn OFF LED (PB0)
		}
	}
	return (0); // End of program (not really needed for embedded systems)
}
