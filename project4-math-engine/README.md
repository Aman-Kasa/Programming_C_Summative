# 🧮 Dynamic Math & Data Processing Engine

A sophisticated C-based mathematical processing system utilizing function pointers for runtime operation selection and dynamic memory management for flexible dataset handling.

## ✨ Features

- **Dynamic Function Dispatch**: Runtime operation selection using function pointers
- **Dynamic Memory Management**: Automatic dataset resizing with malloc/realloc/free
- **Comprehensive Math Operations**: Statistical analysis and mathematical computations
- **Multiple Sorting Algorithms**: Bubble sort and selection sort implementations
- **Advanced Search**: Linear and binary search capabilities
- **File I/O Integration**: Load and save datasets from/to files
- **Interactive Interface**: Menu-driven system for easy operation
- **Memory Safety**: Proper memory management with leak prevention

## 🏗️ Architecture

### Function Pointer System
```c
typedef double (*MathOperation)(Dataset *dataset);
typedef void (*SortOperation)(Dataset *dataset, int ascending);

// Dynamic dispatch table
MathOperationEntry math_operations[] = {
    {"Sum", compute_sum},
    {"Average", compute_average},
    {"Maximum", find_maximum},
    // ...
};
```

### Dynamic Dataset Structure
```c
typedef struct {
    double *data;      // Dynamic array
    int size;          // Current elements
    int capacity;      // Allocated space
} Dataset;
```

## 🚀 Quick Start

```bash
# Compile with math library
make

# Run the engine
./math_engine

# Clean build files
make clean
```

## 📋 Operations Menu

1. **Add Element** - Insert new data point with automatic resizing
2. **Remove Element** - Delete element by index with array compaction
3. **Display Dataset** - Show current dataset contents
4. **Execute Math Operation** - Dynamic function selection and execution
5. **Sort Dataset** - Choose algorithm and sort order at runtime
6. **Search Element** - Linear and binary search demonstrations
7. **Load from File** - Import dataset from text file
8. **Save to File** - Export dataset to text file
9. **Clear Dataset** - Reset dataset to empty state
10. **Exit** - Safe program termination

## 🔢 Mathematical Operations

### Statistical Functions
- **Sum**: Total of all elements
- **Average**: Arithmetic mean calculation
- **Maximum**: Largest value identification
- **Minimum**: Smallest value identification
- **Median**: Middle value computation
- **Standard Deviation**: Statistical dispersion measure

### Implementation Example
```c
// Function pointer execution
double result = math_operations[choice].operation(dataset);
printf("%s: %.6f\n", math_operations[choice].name, result);
```

## 🔄 Sorting Algorithms

### Available Algorithms
- **Bubble Sort**: O(n²) comparison-based sorting
- **Selection Sort**: O(n²) selection-based sorting

### Dynamic Selection
```c
// Runtime algorithm selection
sort_operations[choice].operation(dataset, ascending);
```

## 🔍 Search Operations

- **Linear Search**: O(n) sequential search
- **Binary Search**: O(log n) search on sorted data

## 💾 File Operations

### Data Format
```
12.50
34.75
56.25
78.90
```

### Usage
```c
// Load dataset from file
load_from_file(dataset, "data.txt");

// Save processed results
save_to_file(dataset, "results.txt");
```

## 🧠 Memory Management

### Dynamic Allocation
```c
Dataset* create_dataset(int initial_capacity) {
    Dataset *dataset = malloc(sizeof(Dataset));
    dataset->data = malloc(initial_capacity * sizeof(double));
    dataset->capacity = initial_capacity;
    return dataset;
}
```

### Automatic Resizing
```c
if (dataset->size >= dataset->capacity) {
    dataset->capacity *= 2;
    dataset->data = realloc(dataset->data, 
                           dataset->capacity * sizeof(double));
}
```

## 📁 File Structure

```
project4-math-engine/
├── math_engine.h         # Header declarations
├── math_engine.c         # Core implementation
├── main.c               # User interface
├── Makefile            # Build configuration
├── README.md           # Documentation
└── *.dat               # Data files (generated)
```

## 🎯 Learning Objectives Demonstrated

- ✅ Function pointers and dynamic dispatch
- ✅ Runtime function selection mechanisms
- ✅ Dynamic memory allocation strategies
- ✅ Mathematical algorithm implementation
- ✅ File I/O operations
- ✅ Memory management best practices
- ✅ Modular code architecture

## 🔧 Technical Highlights

### Function Pointer Arrays
```c
// Compile-time operation registration
MathOperationEntry math_operations[] = {
    {"Sum", compute_sum},
    {"Average", compute_average},
    {NULL, NULL}  // Sentinel
};
```

### Runtime Dispatch
```c
// Dynamic operation execution
void execute_math_operation(Dataset *dataset, int choice) {
    double result = math_operations[choice].operation(dataset);
    printf("%s: %.6f\n", math_operations[choice].name, result);
}
```

## 🛡️ Error Handling

- Memory allocation failure detection
- File operation error checking
- Input validation and bounds checking
- Graceful degradation on errors
- Comprehensive error reporting