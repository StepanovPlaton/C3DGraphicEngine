CC = gcc
CFLAGS = -std=gnu23 -Wall -Wextra -O2
LIBS = -lgdi32

WIN_TARGET = main.exe
UNIX_TARGET = main

BASE_SOURCES = main.c engine/engine.c engine/vector.c engine/matrix.c engine/point.c engine/camera.c engine/object.c
WIN_SOURCES = $(BASE_SOURCES) platforms/win.c
WIN_OBJECTS = $(WIN_SOURCES:.c=.wo)
UNIX_SOURCES = $(BASE_SOURCES) platforms/unix.c
UNIX_OBJECTS = $(UNIX_SOURCES:.c=.uo)
MICRO_SOURCES = $(BASE_SOURCES) platforms/micro.c
MICRO_OBJECTS = $(MICRO_SOURCES:.c=.mo)

win: $(WIN_TARGET)
$(WIN_TARGET): $(WIN_OBJECTS)
	$(CC) -o $@ $^ $(LIBS)

%.wo: %.c
	$(CC) $(CFLAGS) -DWIN -c $< -o $@

%.uo: %.c
	$(CC) $(CFLAGS) -DUNIX -c $< -o $@

%.mo: %.c
	$(CC) $(CFLAGS) -DMICRO -c $< -o $@

clean:
	rm -f $(WIN_TARGET) $(WIN_OBJECTS) $(UNIX_OBJECTS) $(MICRO_OBJECTS);

run_win: $(WIN_TARGET)
	.\$(WIN_TARGET)

run_unix: $(UNIX_TARGET)
	.\$(UNIX_TARGET)

.PHONY: all clean rebuild run