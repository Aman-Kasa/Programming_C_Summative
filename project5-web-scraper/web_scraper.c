#include "web_scraper.h"

ScraperManager* init_scraper(int max_threads) {
    ScraperManager *manager = malloc(sizeof(ScraperManager));
    if (!manager) return NULL;
    
    manager->threads = malloc(max_threads * sizeof(ThreadData));
    manager->thread_ids = malloc(max_threads * sizeof(pthread_t));
    
    if (!manager->threads || !manager->thread_ids) {
        free(manager->threads);
        free(manager->thread_ids);
        free(manager);
        return NULL;
    }
    
    manager->count = 0;
    
    // Initialize curl globally
    curl_global_init(CURL_GLOBAL_DEFAULT);
    
    return manager;
}

void free_scraper(ScraperManager *manager) {
    if (manager) {
        free(manager->threads);
        free(manager->thread_ids);
        free(manager);
    }
    curl_global_cleanup();
}

int add_url(ScraperManager *manager, const char *url) {
    if (!manager || manager->count >= MAX_URLS || !is_valid_url(url)) {
        return 0;
    }
    
    ThreadData *thread_data = &manager->threads[manager->count];
    strncpy(thread_data->url, url, MAX_URL_LENGTH - 1);
    thread_data->url[MAX_URL_LENGTH - 1] = '\0';
    
    char *filename = generate_filename(url, manager->count);
    strncpy(thread_data->filename, filename, MAX_FILENAME_LENGTH - 1);
    thread_data->filename[MAX_FILENAME_LENGTH - 1] = '\0';
    free(filename);
    
    thread_data->thread_id = manager->count;
    thread_data->success = 0;
    thread_data->response_code = 0;
    thread_data->download_time = 0.0;
    
    manager->count++;
    return 1;
}

void start_scraping(ScraperManager *manager) {
    printf("Starting %d download threads...\n", manager->count);
    
    for (int i = 0; i < manager->count; i++) {
        int result = pthread_create(&manager->thread_ids[i], NULL, 
                                   scrape_url, &manager->threads[i]);
        if (result != 0) {
            printf("Error creating thread %d: %d\n", i, result);
            manager->threads[i].success = 0;
        }
    }
}

void wait_for_completion(ScraperManager *manager) {
    for (int i = 0; i < manager->count; i++) {
        pthread_join(manager->thread_ids[i], NULL);
    }
    printf("All downloads completed.\n");
}

void* scrape_url(void *arg) {
    ThreadData *data = (ThreadData*)arg;
    CURL *curl;
    CURLcode res;
    WebResponse response = {0};
    
    printf("Thread %d: Starting download from %s\n", data->thread_id, data->url);
    
    curl = curl_easy_init();
    if (!curl) {
        printf("Thread %d: Failed to initialize curl\n", data->thread_id);
        data->success = 0;
        return NULL;
    }
    
    // Set curl options
    curl_easy_setopt(curl, CURLOPT_URL, data->url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30L);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "WebScraper/1.0");
    
    // Perform the request
    double start_time = (double)clock() / CLOCKS_PER_SEC;
    res = curl_easy_perform(curl);
    double end_time = (double)clock() / CLOCKS_PER_SEC;
    
    data->download_time = end_time - start_time;
    
    // Get response code
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &data->response_code);
    
    if (res != CURLE_OK) {
        printf("Thread %d: Download failed: %s\n", data->thread_id, curl_easy_strerror(res));
        data->success = 0;
    } else if (data->response_code != 200) {
        printf("Thread %d: HTTP error %ld\n", data->thread_id, data->response_code);
        data->success = 0;
    } else {
        // Save to file
        FILE *file = fopen(data->filename, "w");
        if (file) {
            if (response.data) {
                fwrite(response.data, 1, response.size, file);
            }
            fclose(file);
            data->success = 1;
            printf("Thread %d: Successfully saved to %s (%.2f KB)\n", 
                   data->thread_id, data->filename, response.size / 1024.0);
        } else {
            printf("Thread %d: Failed to create file %s\n", data->thread_id, data->filename);
            data->success = 0;
        }
    }
    
    // Cleanup
    if (response.data) {
        free(response.data);
    }
    curl_easy_cleanup(curl);
    
    return NULL;
}

size_t write_callback(void *contents, size_t size, size_t nmemb, WebResponse *response) {
    size_t total_size = size * nmemb;
    
    char *new_data = realloc(response->data, response->size + total_size + 1);
    if (!new_data) {
        printf("Memory allocation failed!\n");
        return 0;
    }
    
    response->data = new_data;
    memcpy(&(response->data[response->size]), contents, total_size);
    response->size += total_size;
    response->data[response->size] = '\0';
    
    return total_size;
}

char* generate_filename(const char *url, int thread_id) {
    char *filename = malloc(MAX_FILENAME_LENGTH);
    if (!filename) return NULL;
    
    // Extract domain or use thread ID
    const char *start = strstr(url, "://");
    if (start) {
        start += 3; // Skip "://"
        const char *end = strchr(start, '/');
        if (end) {
            int len = end - start;
            if (len > 20) len = 20; // Limit length
            snprintf(filename, MAX_FILENAME_LENGTH, "thread_%d_%.*s.html", 
                    thread_id, len, start);
        } else {
            snprintf(filename, MAX_FILENAME_LENGTH, "thread_%d_%s.html", thread_id, start);
        }
    } else {
        snprintf(filename, MAX_FILENAME_LENGTH, "thread_%d_content.html", thread_id);
    }
    
    sanitize_filename(filename);
    return filename;
}

void sanitize_filename(char *filename) {
    for (int i = 0; filename[i]; i++) {
        if (filename[i] == ':' || filename[i] == '?' || filename[i] == '*' || 
            filename[i] == '<' || filename[i] == '>' || filename[i] == '|' ||
            filename[i] == '"' || filename[i] == '\\') {
            filename[i] = '_';
        }
    }
}

int is_valid_url(const char *url) {
    return url && (strncmp(url, "http://", 7) == 0 || strncmp(url, "https://", 8) == 0);
}

void print_results(ScraperManager *manager) {
    printf("\n=== Download Results ===\n");
    printf("%-8s %-50s %-12s %-8s %-10s\n", "Thread", "URL", "Status", "Code", "Time(s)");
    printf("--------------------------------------------------------------------------------\n");
    
    for (int i = 0; i < manager->count; i++) {
        ThreadData *data = &manager->threads[i];
        printf("%-8d %-50.47s %-12s %-8ld %-10.3f\n",
               data->thread_id,
               data->url,
               data->success ? "SUCCESS" : "FAILED",
               data->response_code,
               data->download_time);
    }
}

void print_statistics(ScraperManager *manager) {
    int successful = count_successful_downloads(manager);
    double total_time = calculate_total_time(manager);
    
    printf("\n=== Statistics ===\n");
    printf("Total URLs: %d\n", manager->count);
    printf("Successful: %d\n", successful);
    printf("Failed: %d\n", manager->count - successful);
    printf("Success Rate: %.1f%%\n", (double)successful / manager->count * 100);
    printf("Total Download Time: %.3f seconds\n", total_time);
    printf("Average Time per URL: %.3f seconds\n", total_time / manager->count);
}

double calculate_total_time(ScraperManager *manager) {
    double total = 0.0;
    for (int i = 0; i < manager->count; i++) {
        total += manager->threads[i].download_time;
    }
    return total;
}

int count_successful_downloads(ScraperManager *manager) {
    int count = 0;
    for (int i = 0; i < manager->count; i++) {
        if (manager->threads[i].success) {
            count++;
        }
    }
    return count;
}