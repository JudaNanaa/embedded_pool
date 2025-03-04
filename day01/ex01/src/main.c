#include <avr/io.h>
#include <stdbool.h>

#define BIT_CLEAR(reg, bit) (reg &= ~(1 << bit))
#define BIT_SET(reg, bit) (reg |= (1 << bit))

void setup() {
    // Configurer PB1 (OC1A) en sortie
    DDRB |= (1 << PB1);
    
    // Configurer Timer1 en mode CTC avec basculement automatique de OC1A
    TCCR1A = 0;
    BIT_SET(TCCR1A, COM1A0);  // Toggle OC1A sur match
    BIT_CLEAR(TCCR1A, COM1A1);

    // Mode CTC (Clear Timer on Compare Match)
    BIT_CLEAR(TCCR1A, WGM10);
    BIT_CLEAR(TCCR1A, WGM11);
    BIT_SET(TCCR1B, WGM12);
    BIT_CLEAR(TCCR1B, WGM13);

    // Prescaler = 256 (16MHz / 256 = 62.5 kHz)
    BIT_SET(TCCR1B, CS12);
    BIT_CLEAR(TCCR1B, CS11);
    BIT_CLEAR(TCCR1B, CS10);

    // Définir la valeur de comparaison pour une interruption toutes les 500ms
    OCR1A = 31250;

    // Remettre le compteur à 0
    TCNT1 = 0;
}

int main(void) {
    setup();
    
    // Boucle infinie (tout est géré par le Timer1)
    while (true) {
        // Rien à faire ici, OC1A bascule automatiquement
    }
    
    return 0;
}
