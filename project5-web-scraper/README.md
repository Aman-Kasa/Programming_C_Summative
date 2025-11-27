# 🌐 Multi-threaded Web Scraper

A high-performance, concurrent web scraper built in C using POSIX threads (pthreads) for parallel URL fetching and content downloading.

## ✨ Features

- **Parallel Processing**: Simultaneous downloads using multiple threads
- **POSIX Threads**: Efficient pthread implementation for concurrency
- **HTTP/HTTPS Support**: Full support for secure and standard web protocols
- **Error Handling**: Robust error detection and graceful failure recovery
- **File Management**: Automatic file naming and content saving
- **Performance Metrics**: Download statistics and timing analysis
- **URL Validation**: Input validation and URL format checking
- **Batch Processing**: Load multiple URLs from configuration files

## 🏗️ Architecture

### Threading Model
```c
typedef struct {
    char url[MAX_URL_LENGTH];
    char filename[MAX_FILENAME_LENGTH];
    int thread_id;
    int success;
    long response_code;
    double download_time;
} ThreadData;
```

### Concurrent Execution
```c
// Create threads for parallel downloads
for (int i = 0; i < url_count; i++) {
    pthread_create(&threads[i], NULL, scrape_url, &thread_data[i]);
}

// Wait for all threads to complete
for (int i = 0; i < url_count; i++) {
    pthread_join(threads[i], NULL);
}
```

## 🚀 Quick Start

### Prerequisites
```bash
# Install libcurl development package
make install-deps

# Or manually:
# Ubuntu/Debian: sudo apt-get install libcurl4-openssl-dev
# CentOS/RHEL: sudo yum install libcurl-devel
# Arch Linux: sudo pacman -S curl
```

### Build and Run
```bash
# Compile the scraper
make

# Run the application
./web_scraper

# Clean build files
make clean
```

## 📋 Menu Options

1. **Add URL to scrape** - Manually add individual URLs
2. **Load URLs from file** - Batch import from text file
3. **Display current URLs** - Show queued URLs for scraping
4. **Start scraping** - Begin parallel download process
5. **Clear URL list** - Reset the URL queue
6. **Exit** - Safe program termination

## 🔧 Technical Implementation

### Thread Function
```c
void* scrape_url(void *arg) {
    ThreadData *data = (ThreadData*)arg;
    CURL *curl = curl_easy_init();
    
    // Configure curl options
    curl_easy_setopt(curl, CURLOPT_URL, data->url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    
    // Perform download
    CURLcode res = curl_easy_perform(curl);
    
    // Handle response and save to file
    // ...
}
```

### Memory Management
```c
size_t write_callback(void *contents, size_t size, size_t nmemb, WebResponse *response) {
    size_t total_size = size * nmemb;
    
    // Dynamically resize buffer
    char *new_data = realloc(response->data, response->size + total_size + 1);
    memcpy(&(response->data[response->size]), contents, total_size);
    
    return total_size;
}
```

## 📊 Performance Features

### Statistics Tracking
- **Success Rate**: Percentage of successful downloads
- **Response Codes**: HTTP status code monitoring
- **Download Times**: Individual and aggregate timing
- **File Sizes**: Content size analysis

### Sample Output
```
=== Download Results ===
Thread   URL                                          Status      Code     Time(s)
--------------------------------------------------------------------------------
0        https://example.com                          SUCCESS     200      0.245
1        https://httpbin.org/json                     SUCCESS     200      0.312
2        https://invalid-url.com                      FAILED      0        0.000

=== Statistics ===
Total URLs: 3
Successful: 2
Failed: 1
Success Rate: 66.7%
Total Download Time: 0.557 seconds
Average Time per URL: 0.186 seconds
```

## 📁 File Structure

```
project5-web-scraper/
├── web_scraper.h         # Header declarations
├── web_scraper.c         # Core implementation
├── main.c               # User interface
├── Makefile            # Build configuration
├── README.md           # Documentation
├── sample_urls.txt     # Test URLs (generated)
└── thread_*.html       # Downloaded content (generated)
```

## 🌐 URL File Format

Create a text file with one URL per line:
```
https://example.com
https://httpbin.org/html
https://httpbin.org/json
https://httpbin.org/xml
```

## 🎯 Learning Objectives Demonstrated

- ✅ POSIX threads (pthreads) programming
- ✅ Concurrent programming concepts
- ✅ HTTP client implementation
- ✅ Dynamic memory management
- ✅ File I/O operations
- ✅ Error handling in multi-threaded environments
- ✅ Performance measurement and analysis

## 🔒 Thread Safety

- **No Shared State**: Each thread operates on independent data
- **Isolated File Operations**: Separate output files per thread
- **Memory Safety**: Proper allocation and cleanup per thread
- **Error Isolation**: Thread failures don't affect others

## 🛡️ Error Handling

### Network Errors
- Connection timeouts
- DNS resolution failures
- HTTP error codes (404, 500, etc.)
- SSL/TLS certificate issues

### System Errors
- Memory allocation failures
- File creation/write errors
- Thread creation failures
- Invalid URL formats

## 🚀 Advanced Features

- **Automatic Retry**: Built-in retry mechanism for failed downloads
- **Custom Headers**: User-agent and custom HTTP headers
- **Timeout Control**: Configurable connection and read timeouts
- **Content Filtering**: Response size and type validation