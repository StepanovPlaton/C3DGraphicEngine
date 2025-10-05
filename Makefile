CC = gcc
CFLAGS = -std=gnu23 -Wall -Wextra
LIBS = -lgdi32

TARGET = main.exe
SOURCES = main.c utils/utils.c
OBJECTS = $(SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@if command -v rm >/dev/null 2>&1; then \
		rm -f $(TARGET) main.o utils/utils.o; \
	else \
		powershell -Command "Remove-Item -ErrorAction SilentlyContinue '$(TARGET)', 'main.o', 'utils/utils.o'"; \
	fi

rebuild: clean all

run: $(TARGET)
	.\$(TARGET)

.PHONY: all clean rebuild run