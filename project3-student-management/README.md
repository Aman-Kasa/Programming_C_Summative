# 🎓 Advanced Student Management System

A comprehensive C-based student management system featuring dynamic memory allocation, persistent storage, and advanced analytics capabilities.

## ✨ Features

- **Dynamic Memory Management**: Efficient memory allocation with automatic resizing
- **Persistent Storage**: Binary file I/O for data persistence across sessions
- **CRUD Operations**: Complete Create, Read, Update, Delete functionality
- **Advanced Search**: Search by ID or name with optimized algorithms
- **Sorting Algorithms**: Manual implementation of bubble sort for GPA and name
- **Analytics Engine**: Statistical analysis and reporting capabilities
- **Data Validation**: Robust input validation and error handling
- **Memory Safety**: Proper memory management with no leaks

## 🏗️ Architecture

```
Student Structure:
├── ID (unique identifier)
├── Name (string)
├── Age (integer)
├── Course (string)
├── Grades (array of floats)
├── Number of Subjects
└── GPA (calculated)

Database Structure:
├── Students Array (dynamic)
├── Count (current records)
└── Capacity (allocated space)
```

## 🚀 Quick Start

```bash
# Compile the program
make

# Run the application
./student_management

# Clean build files
make clean
```

## 📋 Menu Options

1. **Add Student** - Register new student with validation
2. **Display All Students** - Show formatted student list
3. **Search by ID** - Find student using unique identifier
4. **Search by Name** - Locate student by name
5. **Update Student** - Modify existing student records
6. **Delete Student** - Remove student from database
7. **Sort by GPA** - Arrange students by academic performance
8. **Sort by Name** - Alphabetical ordering of students
9. **Generate Reports** - Comprehensive analytics and statistics
10. **Save to File** - Persist data to binary file
11. **Load from File** - Restore data from storage
12. **Exit** - Safe program termination

## 📊 Analytics Features

- **Class Average GPA**: Overall academic performance metrics
- **Course-wise Analysis**: Performance breakdown by course
- **Top Performers**: Ranking system for academic excellence
- **Statistical Reports**: Comprehensive data insights

## 🔧 Technical Implementation

### Data Structures
- **Dynamic Arrays**: Automatic memory reallocation
- **Structures**: Organized data representation
- **Binary Files**: Efficient data persistence

### Algorithms
- **Bubble Sort**: O(n²) sorting implementation
- **Linear Search**: O(n) search operations
- **Memory Management**: Dynamic allocation/deallocation

### Memory Management
```c
// Dynamic allocation with error checking
StudentDatabase *db = malloc(sizeof(StudentDatabase));
db->students = malloc(capacity * sizeof(Student));

// Automatic resizing
if (count >= capacity) {
    capacity *= 2;
    students = realloc(students, capacity * sizeof(Student));
}
```

## 📁 File Structure

```
project3-student-management/
├── student_management.h    # Header declarations
├── student_management.c    # Core implementation
├── main.c                 # User interface
├── Makefile              # Build configuration
├── README.md             # Documentation
└── students.dat          # Data file (generated)
```

## 🎯 Learning Objectives Demonstrated

- ✅ Advanced C programming with structures
- ✅ Dynamic memory allocation and management
- ✅ File I/O operations (binary format)
- ✅ Algorithm implementation (sorting/searching)
- ✅ Data validation and error handling
- ✅ Modular programming design
- ✅ Statistical analysis and reporting

## 🔍 Sample Usage

```c
// Adding a student
Student student = {
    .id = 1001,
    .name = "John Doe",
    .age = 20,
    .course = "Computer Science",
    .grades = {85.5, 92.0, 78.5, 88.0, 91.5},
    .num_subjects = 5
};
add_student(db, student);
```

## 🛡️ Error Handling

- Input validation for all user data
- Memory allocation failure detection
- File operation error checking
- Duplicate ID prevention
- Graceful error recovery