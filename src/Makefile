# Desktop options
CC = gcc
CFLAGS = -std=gnu23 -Wall -Wextra -O2
CXXFLAGS = -std=gnu++17 -Wall -Wextra -O2 -fno-exceptions -fno-rtti
LIBS = -lgdi32

# Micro options
MCU = atmega328p
F_CPU = 16000000
PROGRAMMER = arduino
PORT = COM5
MICRO_CC = avr-gcc
MICRO_CXX = avr-g++
OBJCOPY = avr-objcopy
SIZE = avr-size
AVRDUDE = avrdude
MICRO_CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU)UL $(CFLAGS) 
MICRO_CXXFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU)UL $(CXXFLAGS)
LDFLAGS = -mmcu=$(MCU)

TARGET = main
BASE_SOURCES = main.c engine/engine.c engine/vector.c engine/matrix.c engine/point.c engine/camera.c engine/object.c utils/math.c

WIN_SOURCES = $(BASE_SOURCES) platforms/win/win.c
WIN_OBJECTS = $(WIN_SOURCES:.c=.wo)
WIN_TARGET = $(TARGET).exe

UNIX_SOURCES = $(BASE_SOURCES) platforms/unix.c
UNIX_OBJECTS = $(UNIX_SOURCES:.c=.uo)
UNIX_TARGET = $(TARGET)

MICRO_SOURCES = $(BASE_SOURCES) platforms/micro/micro.cpp platforms/micro/lib/TVout/TVout.cpp platforms/micro/lib/TVout/video_gen.cpp platforms/micro/lib/MPU6050/MPU6050.c platforms/micro/lib/I2C/I2C.c
MICRO_OBJECTS = $(MICRO_SOURCES:.cpp=.mxxo)
MICRO_OBJECTS := $(MICRO_OBJECTS:.c=.mo)
MICRO_TARGET = $(TARGET)
ELF = $(TARGET).elf
HEX = $(TARGET).hex

win: $(WIN_TARGET)

$(WIN_TARGET): $(WIN_OBJECTS)
	$(CC) -o $@ $^ $(LIBS)

micro: $(HEX)

$(HEX): $(ELF)
	$(OBJCOPY) -O ihex -R .eeprom $< $@
	$(SIZE) $@

$(ELF): $(MICRO_OBJECTS)
	$(MICRO_CXX) $(LDFLAGS) -o $@ $^

%.wo: %.c
	$(CC) $(CFLAGS) -DWIN -c $< -o $@

%.uo: %.c
	$(CC) $(CFLAGS) -DUNIX -c $< -o $@


%.mxxo: %.cpp
	$(MICRO_CXX) $(MICRO_CXXFLAGS) -DMICRO -c $< -o $@

%.mo: %.c
	$(MICRO_CC) $(MICRO_CFLAGS) -DMICRO  -c $< -o $@ 


run_win: $(WIN_TARGET)
	.\$(WIN_TARGET)

run_unix: $(UNIX_TARGET)
	.\$(UNIX_TARGET)

upload_micro: $(HEX)
	$(AVRDUDE) -p $(MCU) -c $(PROGRAMMER) -P $(PORT) -b 57600 -U flash:w:$(HEX):i

clean:
	rm -f $(WIN_TARGET) $(WIN_OBJECTS) $(UNIX_TARGET) $(UNIX_OBJECTS) $(HEX) $(ELF) $(MICRO_OBJECTS);

clean_objects:
	rm -f $(WIN_OBJECTS) $(UNIX_OBJECTS) $(ELF) $(MICRO_OBJECTS);