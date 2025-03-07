# Define the serial port used for programming the microcontroller
PORT = /dev/ttyUSB0

# Define the microcontroller clock frequency (16 MHz for ATmega328P)
F_CPU = 16000000UL

# baudrate is the rate in bits per second that will be transmitted.
BAUDRATE = 115200

# Compiler for AVR (Atmel microcontrollers)
CC = avr-gcc

# Compiler flags:
# -Wall      : Enable common warnings
# -Wextra    : Enable extra warnings
# -Werror    : Treat warnings as errors
# -mmcu      : Specify the microcontroller (ATmega328P)
# -D F_CPU   : Define the CPU frequency
C_FLAGS = -Wall -Wextra -Werror -Os -mmcu=atmega328p -D F_CPU=$(F_CPU) -D BAUDRATE=$(BAUDRATE)

# Tool to convert compiled binaries into HEX files
OBJCOPY = avr-objcopy

# AVR programming tool
ARVDUDE = avrdude

# Flags for converting the binary file to Intel HEX format
OBJCOPY_FLAGS = -O ihex

# Source directory containing the source code
SRCS_DIR = src/

# Source files (adding 'main.c' from 'src/' directory)
SRCS = $(addprefix $(SRCS_DIR), main.c)

# Output binary file name
BINFILE = main.bin

# Output HEX file name
HEXFILE = main.hex

# Default target: build HEX file and flash the microcontroller
all: hex flash

# Target to flash the microcontroller using avrdude
flash:
	$(ARVDUDE) -c arduino -p m328p -P $(PORT) -b $(BAUDRATE) -U flash:w:$(HEXFILE)

# Target to generate the HEX file from the compiled binary
hex: $(BINFILE)
	$(OBJCOPY) $(OBJCOPY_FLAGS) $(BINFILE) $(HEXFILE)

# Target to compile the source code and generate the binary file
$(BINFILE): $(SRCS)
	$(CC) $(C_FLAGS) $^ -o $@

# Target to clean up generated files
clean:
	rm -rf $(BINFILE)
	rm -rf $(HEXFILE)

# Target to clean and rebuild everything
re: clean all

# Mark targets that are not actual files
.PHONY: all flash clean re
