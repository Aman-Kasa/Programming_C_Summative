#ifndef WEB_SCRAPER_H
#define WEB_SCRAPER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <curl/curl.h>
#include <unistd.h>

#define MAX_URL_LENGTH 512
#define MAX_FILENAME_LENGTH 256
#define MAX_URLS 50

typedef struct {
    char *data;
    size_t size;
} WebResponse;

typedef struct {
    char url[MAX_URL_LENGTH];
    char filename[MAX_FILENAME_LENGTH];
    int thread_id;
    int success;
    long response_code;
    double download_time;
} ThreadData;

typedef struct {
    ThreadData *threads;
    int count;
    pthread_t *thread_ids;
} ScraperManager;

// Core functions
ScraperManager* init_scraper(int max_threads);
void free_scraper(ScraperManager *manager);
int add_url(ScraperManager *manager, const char *url);
void start_scraping(ScraperManager *manager);
void wait_for_completion(ScraperManager *manager);
void print_results(ScraperManager *manager);

// Thread function
void* scrape_url(void *arg);

// Utility functions
size_t write_callback(void *contents, size_t size, size_t nmemb, WebResponse *response);
char* generate_filename(const char *url, int thread_id);
int is_valid_url(const char *url);
void sanitize_filename(char *filename);

// Statistics
void print_statistics(ScraperManager *manager);
double calculate_total_time(ScraperManager *manager);
int count_successful_downloads(ScraperManager *manager);

#endif