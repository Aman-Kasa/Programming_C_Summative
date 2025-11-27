#include "web_scraper.h"

void display_menu() {
    printf("\n=== Multi-threaded Web Scraper ===\n");
    printf("1. Add URL to scrape\n");
    printf("2. Load URLs from file\n");
    printf("3. Display current URLs\n");
    printf("4. Start scraping\n");
    printf("5. Clear URL list\n");
    printf("6. Exit\n");
    printf("==================================\n");
    printf("Choose an option: ");
}

int load_urls_from_file(ScraperManager *manager, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: Cannot open file %s\n", filename);
        return 0;
    }
    
    char url[MAX_URL_LENGTH];
    int count = 0;
    
    while (fgets(url, sizeof(url), file)) {
        // Remove newline character
        url[strcspn(url, "\n")] = '\0';
        
        if (strlen(url) > 0 && add_url(manager, url)) {
            count++;
            printf("Added: %s\n", url);
        } else {
            printf("Skipped invalid URL: %s\n", url);
        }
    }
    
    fclose(file);
    printf("Loaded %d URLs from %s\n", count, filename);
    return count;
}

void display_urls(ScraperManager *manager) {
    if (manager->count == 0) {
        printf("No URLs added yet.\n");
        return;
    }
    
    printf("\nCurrent URLs (%d):\n", manager->count);
    for (int i = 0; i < manager->count; i++) {
        printf("%d. %s\n", i + 1, manager->threads[i].url);
    }
}

void create_sample_urls_file() {
    FILE *file = fopen("sample_urls.txt", "w");
    if (file) {
        fprintf(file, "https://httpbin.org/html\n");
        fprintf(file, "https://httpbin.org/json\n");
        fprintf(file, "https://httpbin.org/xml\n");
        fprintf(file, "https://example.com\n");
        fprintf(file, "https://httpbin.org/delay/2\n");
        fclose(file);
        printf("Created sample_urls.txt with test URLs\n");
    }
}

int main() {
    ScraperManager *manager = init_scraper(MAX_URLS);
    if (!manager) {
        printf("Failed to initialize scraper!\n");
        return 1;
    }
    
    int choice;
    char url[MAX_URL_LENGTH];
    char filename[256];
    
    printf("Welcome to Multi-threaded Web Scraper!\n");
    printf("Note: This scraper requires libcurl to be installed.\n");
    
    // Create sample file for testing
    create_sample_urls_file();
    
    while (1) {
        display_menu();
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter URL to scrape: ");
                scanf(" %[^\n]", url);
                
                if (add_url(manager, url)) {
                    printf("URL added successfully!\n");
                } else {
                    printf("Failed to add URL. Check if it's valid and starts with http:// or https://\n");
                }
                break;
                
            case 2:
                printf("Enter filename (or press Enter for 'sample_urls.txt'): ");
                
                // Clear input buffer
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
                
                if (fgets(filename, sizeof(filename), stdin) != NULL) {
                    // Remove newline
                    filename[strcspn(filename, "\n")] = '\0';
                    
                    if (strlen(filename) == 0) {
                        strcpy(filename, "sample_urls.txt");
                    }
                } else {
                    strcpy(filename, "sample_urls.txt");
                }
                
                load_urls_from_file(manager, filename);
                break;
                
            case 3:
                display_urls(manager);
                break;
                
            case 4:
                if (manager->count == 0) {
                    printf("No URLs to scrape! Add some URLs first.\n");
                    break;
                }
                
                printf("Starting parallel download of %d URLs...\n", manager->count);
                start_scraping(manager);
                wait_for_completion(manager);
                print_results(manager);
                print_statistics(manager);
                break;
                
            case 5:
                manager->count = 0;
                printf("URL list cleared.\n");
                break;
                
            case 6:
                free_scraper(manager);
                printf("Goodbye!\n");
                return 0;
                
            default:
                printf("Invalid option! Please try again.\n");
        }
    }
}