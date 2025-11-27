#include "math_engine.h"

void display_menu() {
    printf("\n=== Dynamic Math & Data Processing Engine ===\n");
    printf("1. Add Element\n");
    printf("2. Remove Element\n");
    printf("3. Display Dataset\n");
    printf("4. Execute Math Operation\n");
    printf("5. Sort Dataset\n");
    printf("6. Search Element\n");
    printf("7. Load from File\n");
    printf("8. Save to File\n");
    printf("9. Clear Dataset\n");
    printf("10. Exit\n");
    printf("============================================\n");
    printf("Choose an option: ");
}

void display_math_operations() {
    printf("\nAvailable Math Operations:\n");
    for (int i = 0; math_operations[i].operation != NULL; i++) {
        printf("%d. %s\n", i, math_operations[i].name);
    }
    printf("Choose operation: ");
}

void display_sort_operations() {
    printf("\nAvailable Sort Operations:\n");
    for (int i = 0; sort_operations[i].operation != NULL; i++) {
        printf("%d. %s\n", i, sort_operations[i].name);
    }
    printf("Choose sort algorithm: ");
}

int main() {
    Dataset *dataset = create_dataset(10);
    if (!dataset) {
        printf("Failed to create dataset!\n");
        return 1;
    }
    
    int choice;
    double value;
    int index, operation_choice;
    char filename[256];
    
    printf("Welcome to Dynamic Math & Data Processing Engine!\n");
    
    while (1) {
        display_menu();
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter value to add: ");
                scanf("%lf", &value);
                if (add_element(dataset, value)) {
                    printf("Element %.2f added successfully!\n", value);
                } else {
                    printf("Failed to add element!\n");
                }
                break;
                
            case 2:
                printf("Enter index to remove (0-%d): ", dataset->size - 1);
                scanf("%d", &index);
                if (remove_element(dataset, index)) {
                    printf("Element at index %d removed successfully!\n", index);
                } else {
                    printf("Invalid index!\n");
                }
                break;
                
            case 3:
                print_dataset(dataset);
                break;
                
            case 4:
                display_math_operations();
                scanf("%d", &operation_choice);
                execute_math_operation(dataset, operation_choice);
                break;
                
            case 5:
                display_sort_operations();
                scanf("%d", &operation_choice);
                execute_sort_operation(dataset, operation_choice);
                break;
                
            case 6:
                printf("Enter value to search: ");
                scanf("%lf", &value);
                
                int linear_result = linear_search(dataset, value);
                if (linear_result != -1) {
                    printf("Linear Search: Found at index %d\n", linear_result);
                } else {
                    printf("Linear Search: Not found\n");
                }
                
                // For binary search, we need sorted data
                Dataset *temp = create_dataset(dataset->size);
                for (int i = 0; i < dataset->size; i++) {
                    add_element(temp, dataset->data[i]);
                }
                bubble_sort(temp, 1);
                
                int binary_result = binary_search(temp, value);
                if (binary_result != -1) {
                    printf("Binary Search (on sorted copy): Found at index %d\n", binary_result);
                } else {
                    printf("Binary Search (on sorted copy): Not found\n");
                }
                
                free_dataset(temp);
                break;
                
            case 7:
                printf("Enter filename to load: ");
                scanf("%s", filename);
                if (load_from_file(dataset, filename)) {
                    printf("Data loaded successfully from %s!\n", filename);
                    print_dataset(dataset);
                } else {
                    printf("Failed to load data from %s!\n", filename);
                }
                break;
                
            case 8:
                printf("Enter filename to save: ");
                scanf("%s", filename);
                if (save_to_file(dataset, filename)) {
                    printf("Data saved successfully to %s!\n", filename);
                } else {
                    printf("Failed to save data to %s!\n", filename);
                }
                break;
                
            case 9:
                dataset->size = 0;
                printf("Dataset cleared!\n");
                break;
                
            case 10:
                free_dataset(dataset);
                printf("Goodbye!\n");
                return 0;
                
            default:
                printf("Invalid option! Please try again.\n");
        }
    }
}