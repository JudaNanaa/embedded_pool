# include <avr/io.h>
# include <stdbool.h>

void _ft_delay_ms(unsigned int time_in_ms) {
	volatile unsigned long i, j;
	
	for (i = 0; i < time_in_ms; i++) {
		for (j = 0; j < 1000; j++);
	}
}

int main(void) {
	DDRB |= (1 << PB1);

	while (true) {
		_ft_delay_ms(500);
		PORTB ^= (1 << PB1);
	}
	return 0;
}