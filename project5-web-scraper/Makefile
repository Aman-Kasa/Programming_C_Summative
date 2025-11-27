CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pthread
LIBS = -lcurl
TARGET = web_scraper
SOURCES = main.c web_scraper.c

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES) $(LIBS)

install-deps:
	@echo "Installing libcurl development package..."
	@if command -v apt-get >/dev/null 2>&1; then \
		sudo apt-get update && sudo apt-get install -y libcurl4-openssl-dev; \
	elif command -v yum >/dev/null 2>&1; then \
		sudo yum install -y libcurl-devel; \
	elif command -v pacman >/dev/null 2>&1; then \
		sudo pacman -S curl; \
	else \
		echo "Please install libcurl development package manually"; \
	fi

clean:
	rm -f $(TARGET) *.html sample_urls.txt

.PHONY: clean install-deps