# 🎓 C Programming Summative Assessment Portfolio

<div align="center">
  <img src="https://github.com/Aman-Kasa.png" alt="Aman Kasa" width="150" height="150" style="border-radius: 50%;">
  <h3>Aman Kasa</h3>
  <p><em>African Leadership University (ALU)</em></p>
</div>

A comprehensive collection of advanced C programming projects demonstrating mastery of low-level programming concepts, system programming, and software engineering principles.

## 📋 Portfolio Overview

**Assessment Type**: Individual Portfolio  
**Presentation**: 8-minute comprehensive video demonstration  

## 🎯 Learning Objectives Achieved

- ✅ **String Manipulation**: Advanced C string processing techniques
- ✅ **Function Pointers**: Dynamic function dispatch and runtime selection
- ✅ **Circuit Design**: Hardware-software integration programming
- ✅ **Multi-threading**: Concurrent programming with pthreads
- ✅ **File System Manipulation**: Advanced file I/O with structures
- ✅ **Shell Scripting**: Robust bash script development

## 🚀 Project Portfolio

### 📊 [Project 2: Automated System Monitoring Shell Script](./project2-system-monitor/)
**Technologies**: Bash, System Utilities, Process Management  
**Key Features**:
- Real-time CPU, memory, and disk monitoring
- Configurable threshold alerting system
- Persistent logging with timestamp management
- Interactive menu-driven interface
- Continuous monitoring with customizable intervals

**Highlights**:
```bash
# Quick system status check
./system_monitor.sh

# Continuous monitoring mode
./system_monitor.sh --monitor
```

---

### 🎓 [Project 3: Advanced Student Management System](./project3-student-management/)
**Technologies**: C, Structures, Dynamic Memory, File I/O  
**Key Features**:
- Dynamic memory allocation with automatic resizing
- Binary file persistence for data integrity
- Complete CRUD operations with validation
- Advanced search and sorting algorithms
- Statistical analysis and reporting engine

**Highlights**:
```c
// Dynamic student database with analytics
StudentDatabase *db = init_database();
add_student(db, student);
sort_by_gpa(db);
generate_course_report(db);
```

---

### 🧮 [Project 4: Dynamic Math & Data Processing Engine](./project4-math-engine/)
**Technologies**: C, Function Pointers, Dynamic Memory, Mathematical Algorithms  
**Key Features**:
- Runtime function selection using function pointers
- Dynamic dataset management with automatic resizing
- Comprehensive mathematical operations (statistics, sorting, searching)
- File-based data import/export capabilities
- Modular architecture with pluggable operations

**Highlights**:
```c
// Dynamic operation dispatch
MathOperation ops[] = {{"Sum", compute_sum}, {"Average", compute_average}};
double result = ops[choice].operation(dataset);
```

---

### 🌐 [Project 5: Multi-threaded Web Scraper](./project5-web-scraper/)
**Technologies**: C, POSIX Threads, HTTP/HTTPS, Concurrent Programming  
**Key Features**:
- Parallel URL fetching using pthreads
- HTTP/HTTPS protocol support with libcurl
- Automatic file management and content saving
- Performance metrics and download statistics
- Robust error handling and recovery

**Highlights**:
```c
// Concurrent web scraping
for (int i = 0; i < url_count; i++) {
    pthread_create(&threads[i], NULL, scrape_url, &thread_data[i]);
}
```

## 🏗️ Technical Architecture

### Memory Management Excellence
- **Dynamic Allocation**: Efficient malloc/realloc/free usage
- **Memory Safety**: Zero memory leaks with proper cleanup
- **Error Handling**: Graceful failure recovery mechanisms

### Concurrent Programming Mastery
- **Thread Safety**: Proper synchronization without race conditions
- **Parallel Processing**: Efficient multi-threaded implementations
- **Resource Management**: Optimal thread lifecycle management

### Data Structure Proficiency
- **Custom Structures**: Tailored data representations
- **Algorithm Implementation**: Manual sorting and searching
- **File Persistence**: Binary and text format handling

## 🚀 Quick Start Guide

### Prerequisites
```bash
# Install required dependencies
sudo apt-get update
sudo apt-get install build-essential libcurl4-openssl-dev

# Or use individual project makefiles
cd project5-web-scraper && make install-deps
```

### Build All Projects
```bash
# Navigate to each project and build
for project in project*/; do
    cd "$project"
    if [ -f "Makefile" ]; then
        make clean && make
    fi
    cd ..
done
```

### Run Individual Projects
```bash
# System Monitor
cd project2-system-monitor && ./system_monitor.sh

# Student Management
cd project3-student-management && ./student_management

# Math Engine
cd project4-math-engine && ./math_engine

# Web Scraper (requires libcurl)
cd project5-web-scraper && ./web_scraper
```

## 📊 Project Complexity Matrix

| Project | Memory Mgmt | Concurrency | File I/O | Algorithms | System Calls |
|---------|-------------|-------------|----------|------------|--------------|
| System Monitor | ⭐⭐ | ⭐ | ⭐⭐⭐ | ⭐⭐ | ⭐⭐⭐ |
| Student Mgmt | ⭐⭐⭐ | ⭐ | ⭐⭐⭐ | ⭐⭐⭐ | ⭐⭐ |
| Math Engine | ⭐⭐⭐ | ⭐ | ⭐⭐ | ⭐⭐⭐ | ⭐ |
| Web Scraper | ⭐⭐⭐ | ⭐⭐⭐ | ⭐⭐ | ⭐⭐ | ⭐⭐⭐ |

## 🎯 Technical Excellence

### Core Competencies
- **Code Quality**: Clean, readable, well-documented code
- **Memory Management**: Proper allocation/deallocation practices
- **Error Handling**: Comprehensive error checking and recovery
- **Algorithm Implementation**: Efficient manual implementations
- **System Integration**: Effective use of system resources

### Design Principles
- **Architecture**: Modular, extensible design patterns
- **User Experience**: Intuitive interfaces and clear feedback
- **Performance**: Optimized algorithms and resource usage
- **Robustness**: Graceful handling of edge cases

## 📁 Repository Structure

```
Programming_C_Summative/
├── README.md                           # This comprehensive overview
├── project2-system-monitor/            # Shell scripting & system monitoring
│   ├── system_monitor.sh              # Main monitoring script
│   ├── README.md                      # Project documentation
│   └── monitor_config.conf            # Configuration file
├── project3-student-management/        # Structures & file handling
│   ├── student_management.h           # Header declarations
│   ├── student_management.c           # Core implementation
│   ├── main.c                         # User interface
│   ├── Makefile                       # Build configuration
│   └── README.md                      # Project documentation
├── project4-math-engine/              # Function pointers & dynamic memory
│   ├── math_engine.h                  # Header declarations
│   ├── math_engine.c                  # Core implementation
│   ├── main.c                         # User interface
│   ├── Makefile                       # Build configuration
│   └── README.md                      # Project documentation
└── project5-web-scraper/              # Multi-threading & network programming
    ├── web_scraper.h                  # Header declarations
    ├── web_scraper.c                  # Core implementation
    ├── main.c                         # User interface
    ├── Makefile                       # Build configuration
    └── README.md                      # Project documentation
```

## 🏆 Key Achievements

### Advanced C Programming
- **Function Pointers**: Dynamic dispatch mechanisms
- **Memory Management**: Zero-leak implementations
- **Data Structures**: Custom structure design and manipulation
- **File I/O**: Binary and text format handling

### System Programming
- **Process Management**: System monitoring and control
- **Thread Programming**: Concurrent execution models
- **Network Programming**: HTTP client implementation
- **Shell Scripting**: Advanced bash programming

### Software Engineering
- **Modular Design**: Clean separation of concerns
- **Error Handling**: Comprehensive error management
- **Documentation**: Professional-grade documentation
- **Testing**: Robust validation and edge case handling

## 🎬 Video Presentation Structure

**Duration**: 8 minutes maximum  
**Content Coverage**:
1. **Introduction** (1 min) - Portfolio overview and objectives
2. **System Monitor Demo** (1.5 min) - Real-time monitoring capabilities
3. **Student Management** (2 min) - CRUD operations and analytics
4. **Math Engine** (2 min) - Function pointers and dynamic operations
5. **Web Scraper** (1 min) - Multi-threaded concurrent downloads
6. **Technical Highlights** (0.5 min) - Key programming concepts demonstrated

## 🔧 Development Environment

**Compiler**: GCC with C99 standard  
**Build System**: Make with custom Makefiles  
**Dependencies**: POSIX threads, libcurl, standard C libraries  
**Platform**: Linux/Unix compatible  
**Version Control**: Git with structured commits  

## 📈 Performance Metrics

- **Memory Efficiency**: Dynamic allocation with minimal overhead
- **Execution Speed**: Optimized algorithms for performance
- **Scalability**: Handles large datasets and multiple concurrent operations
- **Reliability**: Robust error handling with graceful degradation

---

**Author**: Aman Kasa  
**Course**: Low-Level Programming  
**Institution**: African Leadership University (ALU)  
**Instructor**: Thadee  
**GitHub**: [@Aman-Kasa](https://github.com/Aman-Kasa)  

*This portfolio demonstrates comprehensive mastery of C programming, system programming concepts, and software engineering best practices through practical, real-world applications.*