#include "math_engine.h"
#include <math.h>

// Function pointer arrays for dynamic dispatch
MathOperationEntry math_operations[] = {
    {"Sum", compute_sum},
    {"Average", compute_average},
    {"Maximum", find_maximum},
    {"Minimum", find_minimum},
    {"Median", compute_median},
    {"Standard Deviation", compute_std_deviation},
    {NULL, NULL}
};

SortOperationEntry sort_operations[] = {
    {"Bubble Sort", bubble_sort},
    {"Selection Sort", selection_sort},
    {NULL, NULL}
};

Dataset* create_dataset(int initial_capacity) {
    Dataset *dataset = malloc(sizeof(Dataset));
    if (!dataset) return NULL;
    
    dataset->data = malloc(initial_capacity * sizeof(double));
    if (!dataset->data) {
        free(dataset);
        return NULL;
    }
    
    dataset->size = 0;
    dataset->capacity = initial_capacity;
    return dataset;
}

void free_dataset(Dataset *dataset) {
    if (dataset) {
        free(dataset->data);
        free(dataset);
    }
}

int add_element(Dataset *dataset, double value) {
    if (dataset->size >= dataset->capacity) {
        dataset->capacity *= 2;
        double *temp = realloc(dataset->data, dataset->capacity * sizeof(double));
        if (!temp) return 0;
        dataset->data = temp;
    }
    
    dataset->data[dataset->size++] = value;
    return 1;
}

int remove_element(Dataset *dataset, int index) {
    if (index < 0 || index >= dataset->size) return 0;
    
    for (int i = index; i < dataset->size - 1; i++) {
        dataset->data[i] = dataset->data[i + 1];
    }
    dataset->size--;
    return 1;
}

void print_dataset(Dataset *dataset) {
    printf("Dataset [%d elements]: ", dataset->size);
    for (int i = 0; i < dataset->size; i++) {
        printf("%.2f ", dataset->data[i]);
    }
    printf("\n");
}

double compute_sum(Dataset *dataset) {
    double sum = 0.0;
    for (int i = 0; i < dataset->size; i++) {
        sum += dataset->data[i];
    }
    return sum;
}

double compute_average(Dataset *dataset) {
    if (dataset->size == 0) return 0.0;
    return compute_sum(dataset) / dataset->size;
}

double find_maximum(Dataset *dataset) {
    if (dataset->size == 0) return 0.0;
    
    double max = dataset->data[0];
    for (int i = 1; i < dataset->size; i++) {
        if (dataset->data[i] > max) {
            max = dataset->data[i];
        }
    }
    return max;
}

double find_minimum(Dataset *dataset) {
    if (dataset->size == 0) return 0.0;
    
    double min = dataset->data[0];
    for (int i = 1; i < dataset->size; i++) {
        if (dataset->data[i] < min) {
            min = dataset->data[i];
        }
    }
    return min;
}

double compute_median(Dataset *dataset) {
    if (dataset->size == 0) return 0.0;
    
    // Create a copy for sorting
    Dataset *temp = create_dataset(dataset->size);
    for (int i = 0; i < dataset->size; i++) {
        add_element(temp, dataset->data[i]);
    }
    
    bubble_sort(temp, 1); // Sort ascending
    
    double median;
    if (temp->size % 2 == 0) {
        median = (temp->data[temp->size/2 - 1] + temp->data[temp->size/2]) / 2.0;
    } else {
        median = temp->data[temp->size/2];
    }
    
    free_dataset(temp);
    return median;
}

double compute_std_deviation(Dataset *dataset) {
    if (dataset->size <= 1) return 0.0;
    
    double mean = compute_average(dataset);
    double sum_squared_diff = 0.0;
    
    for (int i = 0; i < dataset->size; i++) {
        double diff = dataset->data[i] - mean;
        sum_squared_diff += diff * diff;
    }
    
    return sqrt(sum_squared_diff / (dataset->size - 1));
}

void bubble_sort(Dataset *dataset, int ascending) {
    for (int i = 0; i < dataset->size - 1; i++) {
        for (int j = 0; j < dataset->size - i - 1; j++) {
            int should_swap = ascending ? 
                (dataset->data[j] > dataset->data[j + 1]) :
                (dataset->data[j] < dataset->data[j + 1]);
            
            if (should_swap) {
                double temp = dataset->data[j];
                dataset->data[j] = dataset->data[j + 1];
                dataset->data[j + 1] = temp;
            }
        }
    }
}

void selection_sort(Dataset *dataset, int ascending) {
    for (int i = 0; i < dataset->size - 1; i++) {
        int target_idx = i;
        
        for (int j = i + 1; j < dataset->size; j++) {
            int should_select = ascending ?
                (dataset->data[j] < dataset->data[target_idx]) :
                (dataset->data[j] > dataset->data[target_idx]);
            
            if (should_select) {
                target_idx = j;
            }
        }
        
        if (target_idx != i) {
            double temp = dataset->data[i];
            dataset->data[i] = dataset->data[target_idx];
            dataset->data[target_idx] = temp;
        }
    }
}

int linear_search(Dataset *dataset, double value) {
    for (int i = 0; i < dataset->size; i++) {
        if (fabs(dataset->data[i] - value) < 0.001) {
            return i;
        }
    }
    return -1;
}

int binary_search(Dataset *dataset, double value) {
    int left = 0, right = dataset->size - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (fabs(dataset->data[mid] - value) < 0.001) {
            return mid;
        }
        
        if (dataset->data[mid] < value) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

int load_from_file(Dataset *dataset, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) return 0;
    
    dataset->size = 0; // Reset dataset
    double value;
    
    while (fscanf(file, "%lf", &value) == 1) {
        if (!add_element(dataset, value)) {
            fclose(file);
            return 0;
        }
    }
    
    fclose(file);
    return 1;
}

int save_to_file(Dataset *dataset, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) return 0;
    
    for (int i = 0; i < dataset->size; i++) {
        fprintf(file, "%.6f\n", dataset->data[i]);
    }
    
    fclose(file);
    return 1;
}

void execute_math_operation(Dataset *dataset, int choice) {
    if (choice < 0 || math_operations[choice].operation == NULL) {
        printf("Invalid operation choice!\n");
        return;
    }
    
    if (dataset->size == 0) {
        printf("Dataset is empty!\n");
        return;
    }
    
    double result = math_operations[choice].operation(dataset);
    printf("%s: %.6f\n", math_operations[choice].name, result);
}

void execute_sort_operation(Dataset *dataset, int choice) {
    if (choice < 0 || sort_operations[choice].operation == NULL) {
        printf("Invalid sort choice!\n");
        return;
    }
    
    if (dataset->size == 0) {
        printf("Dataset is empty!\n");
        return;
    }
    
    int order;
    printf("Sort order (1=Ascending, 0=Descending): ");
    scanf("%d", &order);
    
    sort_operations[choice].operation(dataset, order);
    printf("Dataset sorted using %s (%s)\n", 
           sort_operations[choice].name, 
           order ? "Ascending" : "Descending");
}