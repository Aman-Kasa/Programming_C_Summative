#ifndef MATH_ENGINE_H
#define MATH_ENGINE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    double *data;
    int size;
    int capacity;
} Dataset;

// Function pointer type for operations
typedef double (*MathOperation)(Dataset *dataset);
typedef void (*SortOperation)(Dataset *dataset, int ascending);
typedef int (*SearchOperation)(Dataset *dataset, double value);

// Dataset management
Dataset* create_dataset(int initial_capacity);
void free_dataset(Dataset *dataset);
int add_element(Dataset *dataset, double value);
int remove_element(Dataset *dataset, int index);
void print_dataset(Dataset *dataset);

// Mathematical operations
double compute_sum(Dataset *dataset);
double compute_average(Dataset *dataset);
double find_maximum(Dataset *dataset);
double find_minimum(Dataset *dataset);
double compute_median(Dataset *dataset);
double compute_std_deviation(Dataset *dataset);

// Sorting operations
void bubble_sort(Dataset *dataset, int ascending);
void selection_sort(Dataset *dataset, int ascending);

// Search operations
int linear_search(Dataset *dataset, double value);
int binary_search(Dataset *dataset, double value);

// File operations
int load_from_file(Dataset *dataset, const char *filename);
int save_to_file(Dataset *dataset, const char *filename);

// Operation dispatcher
typedef struct {
    const char *name;
    MathOperation operation;
} MathOperationEntry;

typedef struct {
    const char *name;
    SortOperation operation;
} SortOperationEntry;

// Function pointer arrays
extern MathOperationEntry math_operations[];
extern SortOperationEntry sort_operations[];

// Utility functions
void display_menu();
int get_operation_choice(const char *type);
void execute_math_operation(Dataset *dataset, int choice);
void execute_sort_operation(Dataset *dataset, int choice);

#endif