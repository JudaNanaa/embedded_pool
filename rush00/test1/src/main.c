#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <util/twi.h>

// I2C communication settings
#define I2C_ADDR 0x20
#define I2C_TIMEOUT 100

// Device roles
typedef enum {
    ROLE_UNDETERMINED, // Role not yet determined
    ROLE_MASTER,       // This device is I2C master
    ROLE_SLAVE         // This device is I2C slave
} DeviceRole;

volatile DeviceRole deviceRole = ROLE_UNDETERMINED;

// Function prototypes
void initIO(void);
void initI2C(void);
void determineRole(void);
void i2cSendByte(uint8_t data);
uint8_t i2cReceiveByte(void);

// I2C interrupt service routine
ISR(TWI_vect) {
    // Basic I2C interrupt handler
    switch (TW_STATUS) {
        // Master transmitter mode
        // case TW_START:
        // case TW_REP_START:
        //     TWDR = I2C_ADDR << 1 | TW_WRITE;
        //     TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWIE);
        //     break;
            
        // case TW_MT_SLA_ACK:
        // case TW_MT_DATA_ACK:
        //     // Data sent and ACK received
        //     TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO) | (1<<TWIE);
        //     break;
            
        // // Slave receiver mode
        // case TW_SR_GCALL_ACK:
        case TW_SR_SLA_ACK:
        case TW_SR_DATA_ACK:
			TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWIE) | (1<<TWEA);
        // case TW_SR_GCALL_DATA_ACK:
        //     // Data received
        //     TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWIE) | (1<<TWEA);
        //     break;
            
        // //Slave transmitter mode
        // case TW_ST_SLA_ACK:
        // case TW_ST_DATA_ACK:
        //     // Send data if requested
        //     TWDR = 0x00; // Default response
        //     TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWIE) | (1<<TWEA);
        //     break;
            
        // //Error states
        // case TW_BUS_ERROR:
        //     TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWIE) | (1<<TWSTO) | (1<<TWEA);
        //     break;
		    
        default:
            TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWIE) | (1<<TWEA);
            break;
    }
}

int main(void) {
    // Initialize
    initIO();
    initI2C();
    
    // Enable interrupts
    sei();
    
    // Determine role (master/slave)
    determineRole();
    
    // Simple communication loop
    while (1) {
        if (deviceRole == ROLE_MASTER) {
            // Master sends a byte every second
			PORTB ^= (23);
            i2cSendByte(0x42);  // Send arbitrary data
			
            _delay_ms(1000);    // Wait 1 second
			PORTB ^= (23);
        }
        // Slave just waits for data in the ISR
        
        _delay_ms(10); // Small delay to prevent CPU hogging
    }
    
    return 0;
}

// Initialize I/O ports (basic setup)
void initIO(void) {
    // Set LED pin as output (for status indication)
    DDRB |= (1 << PB0);
    DDRB |= 23;
	// led slave / master
	DDRD |= (1 << PD5);
	DDRD |= (1 << PD6);

    // Set button pin as input with pull-up
    DDRD &= ~(1 << PD2);
    PORTD |= (1 << PD2);
}

// Initialize I2C
void initI2C(void) {
    // Set I2C clock frequency to 100kHz (16MHz / (16 + 2*TWBR*4^TWPS))
    TWBR = 72; // For 100kHz with 16MHz clock
    TWSR = 0;  // Prescaler = 1
    
    // Enable I2C and interrupts
    TWCR = (1 << TWEN) | (1 << TWIE) | (1 << TWEA);
    
    // Set slave address
    TWAR = I2C_ADDR << 1;
}

// Determine if this device should be master or slave
void determineRole(void) {
    // Try to become master by sending start condition
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    
    // Wait for start condition to be transmitted or timeout
    uint8_t timeout = I2C_TIMEOUT;
    while (!(TWCR & (1 << TWINT)) && timeout) {
        _delay_ms(1);
        timeout--;
    }
    
    if (timeout) {
        // Successfully sent start condition, become master
        deviceRole = ROLE_MASTER;
        TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN) | (1 << TWIE) | (1 << TWEA);
        
        // Indicate master role with LED
        PORTD |= (1 << PD5);
    } else {
        // Failed to send start condition, become slave
        deviceRole = ROLE_SLAVE;
        TWCR = (1 << TWEN) | (1 << TWIE) | (1 << TWEA);
        
        // Indicate slave role with LED off
        PORTD |= (1 << PD6);
    }
}

// Send a byte over I2C (master mode)
void i2cSendByte(uint8_t data) {
    if (deviceRole != ROLE_MASTER) return;
    
    // Send start condition
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)));
	
    // Send slave address with write bit
    TWDR = I2C_ADDR << 1 | TW_WRITE;            
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)));  /*LOCKED*/
    
    // Send data
    TWDR = data;
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)));
    
    // Send stop condition
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
}

// Receive a byte over I2C (master mode)
uint8_t i2cReceiveByte(void) {
    if (deviceRole != ROLE_MASTER) return 0;
    
    uint8_t data;
    
    // Send start condition
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)));
    
    // Send slave address with read bit
    TWDR = I2C_ADDR << 1 | TW_READ;
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)));
    
    // Receive data with NACK (last byte)
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)));
    data = TWDR;
    
    // Send stop condition
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
    
    return data;
}