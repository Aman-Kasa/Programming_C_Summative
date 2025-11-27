CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = student_management
SOURCES = main.c student_management.c

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET) students.dat

.PHONY: clean