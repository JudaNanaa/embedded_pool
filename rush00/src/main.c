#include "../includes/includes.h"
#include <stdint.h>

volatile uint8_t status = 0xF8;

//TWCR (TWI Control Register) : Utilisé pour contrôler le périphérique I2C (démarrer, arrêter, acquitter, etc.).
void TWI_init_master(void) {
    // Définir la fréquence SCL (ex: 100kHz avec F_CPU = 16MHz)
    TWBR = 72; // Voir la formule du datasheet
    TWSR = 0x00; // Prescaler = 1
    // Activer TWI
    TWCR = (1 << TWEN); // TWEN (TWI Enable Bit) : Active l’interface I2C
}

void TWI_init_slave(uint8_t address) {
    TWAR = address << 1; // Définir l'adresse de l'esclave (ex: 0x10)
    TWCR = (1 << TWEN) | (1 << TWEA); // Activer TWI en mode esclave et répondre aux requêtes
}


ISR(TWI_vect) {
	status = (TWSR & 0xF8);
}

void twi_init(uint32_t speed)
{
	uint32_t gen_t = 0;
	
	gen_t = (((F_CPU / speed) - 16) / 2) & 0xFF ;
	TWSR = 0x00; 
	TWBR = gen_t & 0xFF;
	TWCR = ( 1<<TWIE ) | (1<<TWEN);
}

uint8_t twi_start(void) {
	uint16_t i = 0;

	TWCR = (1 << TWINT) | (1 << TWSTA) | (1<<TWEN);
	while (!(TWCR & (1<<TWINT)));

	return TWI_OK;
}

void twi_stop(void) {
	TWCR = (1 << TWINT) | (1 << TWSTO) | (1<<TWEN) | ( 1<<TWIE );

}

uint8_t twi_restart(void) {
	uint16_t i = 0;

	TWCR = (1 << TWINT) | (1 << TWSTA) | (1<<TWEN) | ( 1<<TWIE );
	while (status != TWI_RESTART) {
		if (i >= TWI_TIMEOUT) {
			return TWI_ERROR_START;
		}
		i++;
	}

	return TWI_OK;
}

int main ()
{
	while ((twi_start() != TWI_OK));

}