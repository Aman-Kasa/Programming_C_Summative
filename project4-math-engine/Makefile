CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LIBS = -lm
TARGET = math_engine
SOURCES = main.c math_engine.c

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES) $(LIBS)

clean:
	rm -f $(TARGET) *.dat

.PHONY: clean