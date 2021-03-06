###############################################################################
# Makefile for the project can_collector_node_example_gcc
###############################################################################

## General Flags
PROJECT = can_collector_node_example_gcc
MCU = at90can128
TARGET = can_collector_node_example_gcc.elf
CC = avr-gcc
ProgrammerMCU = c128
AVRDUDE = avrdude

## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -Wall -gdwarf-2  -O0 -funsigned-char -funsigned-bitfields
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d 

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += $(CFLAGS)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS +=  -Wl,-Map=can_collector_node_example_gcc.map


## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings


## Include Directories
INCLUDES = -I "lib"

## Objects that must be built in order to link
OBJECTS = main_collector_node_example.o can_drv.o can_lib.o led_drv.o rtc_drv.o uart_drv.o uart_lib.o 

## Objects explicitly added by the user
LINKONLYOBJECTS = 

## Brænd for satan
## install: avrdude -c avrispmkii -P usb -p $(ProgrammerMCU) -U flash:w:can_collector_node_example_gcc.hex



## Build
all: $(TARGET) can_collector_node_example_gcc.hex can_collector_node_example_gcc.eep can_collector_node_example_gcc.lss

## Compile
main_collector_node_example.o: main_collector_node_example.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

can_drv.o: lib/can_drv.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

can_lib.o: lib/can_lib.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

led_drv.o: lib/led_drv.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

rtc_drv.o: lib/rtc_drv.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

uart_drv.o: lib/uart_drv.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

uart_lib.o: lib/uart_lib.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

##Link
$(TARGET): $(OBJECTS)
	 $(CC) $(LDFLAGS) $(OBJECTS) $(LINKONLYOBJECTS) $(LIBDIRS) $(LIBS) -o $(TARGET)

%.hex: $(TARGET)
	avr-objcopy -O ihex $(HEX_FLASH_FLAGS)  $< $@

%.eep: $(TARGET)
	-avr-objcopy $(HEX_EEPROM_FLAGS) -O ihex $< $@ || exit 0

%.lss: $(TARGET)
	avr-objdump -h -S $< > $@

size: ${TARGET}
	@echo
	@avr-size -C --mcu=${MCU} ${TARGET}

## Clean target
.PHONY: clean
clean:
	-rm -rf $(OBJECTS) can_collector_node_example_gcc.elf dep/* can_collector_node_example_gcc.hex can_collector_node_example_gcc.eep can_collector_node_example_gcc.lss can_collector_node_example_gcc.map


## Other dependencies
-include $(shell mkdir dep 2>/dev/null) $(wildcard dep/*)
