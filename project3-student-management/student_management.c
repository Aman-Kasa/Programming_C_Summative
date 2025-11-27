#include "student_management.h"

StudentDatabase* init_database() {
    StudentDatabase *db = malloc(sizeof(StudentDatabase));
    if (!db) return NULL;
    
    db->students = malloc(10 * sizeof(Student));
    if (!db->students) {
        free(db);
        return NULL;
    }
    
    db->count = 0;
    db->capacity = 10;
    return db;
}

void free_database(StudentDatabase *db) {
    if (db) {
        free(db->students);
        free(db);
    }
}

int add_student(StudentDatabase *db, Student student) {
    if (!db || !validate_student_data(&student)) return 0;
    
    // Check for duplicate ID
    if (search_by_id(db, student.id)) return 0;
    
    // Resize if needed
    if (db->count >= db->capacity) {
        db->capacity *= 2;
        Student *temp = realloc(db->students, db->capacity * sizeof(Student));
        if (!temp) return 0;
        db->students = temp;
    }
    
    student.gpa = calculate_gpa(student.grades, student.num_subjects);
    db->students[db->count++] = student;
    return 1;
}

int update_student(StudentDatabase *db, int id, Student updated) {
    Student *student = search_by_id(db, id);
    if (!student || !validate_student_data(&updated)) return 0;
    
    updated.gpa = calculate_gpa(updated.grades, updated.num_subjects);
    *student = updated;
    return 1;
}

int delete_student(StudentDatabase *db, int id) {
    for (int i = 0; i < db->count; i++) {
        if (db->students[i].id == id) {
            for (int j = i; j < db->count - 1; j++) {
                db->students[j] = db->students[j + 1];
            }
            db->count--;
            return 1;
        }
    }
    return 0;
}

void display_students(StudentDatabase *db) {
    printf("\n=== Student Records ===\n");
    printf("%-5s %-20s %-5s %-15s %-8s\n", "ID", "Name", "Age", "Course", "GPA");
    printf("--------------------------------------------------------\n");
    
    for (int i = 0; i < db->count; i++) {
        printf("%-5d %-20s %-5d %-15s %.2f\n",
               db->students[i].id, db->students[i].name,
               db->students[i].age, db->students[i].course,
               db->students[i].gpa);
    }
}

Student* search_by_id(StudentDatabase *db, int id) {
    for (int i = 0; i < db->count; i++) {
        if (db->students[i].id == id) {
            return &db->students[i];
        }
    }
    return NULL;
}

Student* search_by_name(StudentDatabase *db, const char *name) {
    for (int i = 0; i < db->count; i++) {
        if (strcmp(db->students[i].name, name) == 0) {
            return &db->students[i];
        }
    }
    return NULL;
}

int save_to_file(StudentDatabase *db) {
    FILE *file = fopen(DATA_FILE, "wb");
    if (!file) return 0;
    
    fwrite(&db->count, sizeof(int), 1, file);
    fwrite(db->students, sizeof(Student), db->count, file);
    fclose(file);
    return 1;
}

int load_from_file(StudentDatabase *db) {
    FILE *file = fopen(DATA_FILE, "rb");
    if (!file) return 0;
    
    int count;
    if (fread(&count, sizeof(int), 1, file) != 1) {
        fclose(file);
        return 0;
    }
    
    if (count > db->capacity) {
        Student *temp = realloc(db->students, count * sizeof(Student));
        if (!temp) {
            fclose(file);
            return 0;
        }
        db->students = temp;
        db->capacity = count;
    }
    
    if (fread(db->students, sizeof(Student), count, file) != count) {
        fclose(file);
        return 0;
    }
    
    db->count = count;
    fclose(file);
    return 1;
}

void sort_by_gpa(StudentDatabase *db) {
    for (int i = 0; i < db->count - 1; i++) {
        for (int j = 0; j < db->count - i - 1; j++) {
            if (db->students[j].gpa < db->students[j + 1].gpa) {
                Student temp = db->students[j];
                db->students[j] = db->students[j + 1];
                db->students[j + 1] = temp;
            }
        }
    }
}

void sort_by_name(StudentDatabase *db) {
    for (int i = 0; i < db->count - 1; i++) {
        for (int j = 0; j < db->count - i - 1; j++) {
            if (strcmp(db->students[j].name, db->students[j + 1].name) > 0) {
                Student temp = db->students[j];
                db->students[j] = db->students[j + 1];
                db->students[j + 1] = temp;
            }
        }
    }
}

float calculate_class_average(StudentDatabase *db) {
    if (db->count == 0) return 0.0;
    
    float total = 0.0;
    for (int i = 0; i < db->count; i++) {
        total += db->students[i].gpa;
    }
    return total / db->count;
}

void sort_by_id(StudentDatabase *db) {
    for (int i = 0; i < db->count - 1; i++) {
        for (int j = 0; j < db->count - i - 1; j++) {
            if (db->students[j].id > db->students[j + 1].id) {
                Student temp = db->students[j];
                db->students[j] = db->students[j + 1];
                db->students[j + 1] = temp;
            }
        }
    }
}

float calculate_median_gpa(StudentDatabase *db) {
    if (db->count == 0) return 0.0;
    
    // Create temporary array for sorting
    float *gpas = malloc(db->count * sizeof(float));
    for (int i = 0; i < db->count; i++) {
        gpas[i] = db->students[i].gpa;
    }
    
    // Sort GPAs
    for (int i = 0; i < db->count - 1; i++) {
        for (int j = 0; j < db->count - i - 1; j++) {
            if (gpas[j] > gpas[j + 1]) {
                float temp = gpas[j];
                gpas[j] = gpas[j + 1];
                gpas[j + 1] = temp;
            }
        }
    }
    
    float median;
    if (db->count % 2 == 0) {
        median = (gpas[db->count/2 - 1] + gpas[db->count/2]) / 2.0;
    } else {
        median = gpas[db->count/2];
    }
    
    free(gpas);
    return median;
}

Student* find_highest_gpa(StudentDatabase *db) {
    if (db->count == 0) return NULL;
    
    Student *highest = &db->students[0];
    for (int i = 1; i < db->count; i++) {
        if (db->students[i].gpa > highest->gpa) {
            highest = &db->students[i];
        }
    }
    return highest;
}

Student* find_lowest_gpa(StudentDatabase *db) {
    if (db->count == 0) return NULL;
    
    Student *lowest = &db->students[0];
    for (int i = 1; i < db->count; i++) {
        if (db->students[i].gpa < lowest->gpa) {
            lowest = &db->students[i];
        }
    }
    return lowest;
}

Student* get_top_student_by_course(StudentDatabase *db, const char *course) {
    Student *top = NULL;
    float highest_gpa = -1.0;
    
    for (int i = 0; i < db->count; i++) {
        if (strcmp(db->students[i].course, course) == 0) {
            if (db->students[i].gpa > highest_gpa) {
                highest_gpa = db->students[i].gpa;
                top = &db->students[i];
            }
        }
    }
    return top;
}

void display_top_n_students(StudentDatabase *db, int n) {
    if (n > db->count) n = db->count;
    
    // Sort by GPA first
    sort_by_gpa(db);
    
    printf("\n=== Top %d Students ===\n", n);
    printf("%-5s %-20s %-15s %-8s\n", "Rank", "Name", "Course", "GPA");
    printf("------------------------------------------------\n");
    
    for (int i = 0; i < n; i++) {
        printf("%-5d %-20s %-15s %.2f\n", 
               i + 1, db->students[i].name, 
               db->students[i].course, db->students[i].gpa);
    }
}

int binary_search_by_id(StudentDatabase *db, int id) {
    // First sort by ID
    sort_by_id(db);
    
    int left = 0, right = db->count - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (db->students[mid].id == id) {
            return mid;
        }
        
        if (db->students[mid].id < id) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return -1; // Not found
}

void generate_course_report(StudentDatabase *db) {
    printf("\n=== Advanced Course Analytics ===\n");
    
    char courses[50][MAX_COURSE_LEN];
    float course_totals[50] = {0};
    int course_counts[50] = {0};
    int unique_courses = 0;
    
    for (int i = 0; i < db->count; i++) {
        int found = 0;
        for (int j = 0; j < unique_courses; j++) {
            if (strcmp(courses[j], db->students[i].course) == 0) {
                course_totals[j] += db->students[i].gpa;
                course_counts[j]++;
                found = 1;
                break;
            }
        }
        if (!found) {
            strcpy(courses[unique_courses], db->students[i].course);
            course_totals[unique_courses] = db->students[i].gpa;
            course_counts[unique_courses] = 1;
            unique_courses++;
        }
    }
    
    for (int i = 0; i < unique_courses; i++) {
        float avg = course_totals[i] / course_counts[i];
        Student *top = get_top_student_by_course(db, courses[i]);
        
        printf("\nCourse: %s\n", courses[i]);
        printf("  Average GPA: %.2f\n", avg);
        printf("  Students: %d\n", course_counts[i]);
        if (top) {
            printf("  Top Student: %s (%.2f GPA)\n", top->name, top->gpa);
        }
    }
    
    // Overall statistics
    printf("\n=== Overall Statistics ===\n");
    printf("Total Students: %d\n", db->count);
    printf("Class Average: %.2f\n", calculate_class_average(db));
    printf("Median GPA: %.2f\n", calculate_median_gpa(db));
    
    Student *highest = find_highest_gpa(db);
    Student *lowest = find_lowest_gpa(db);
    
    if (highest) {
        printf("Highest GPA: %s (%.2f)\n", highest->name, highest->gpa);
    }
    if (lowest) {
        printf("Lowest GPA: %s (%.2f)\n", lowest->name, lowest->gpa);
    }
}

// Convert percentage grade to 4.0 GPA scale
float grade_to_gpa(float grade) {
    if (grade >= 97) return 4.0;  // A+
    if (grade >= 93) return 4.0;  // A
    if (grade >= 90) return 3.7;  // A-
    if (grade >= 87) return 3.3;  // B+
    if (grade >= 83) return 3.0;  // B
    if (grade >= 80) return 2.7;  // B-
    if (grade >= 77) return 2.3;  // C+
    if (grade >= 73) return 2.0;  // C
    if (grade >= 70) return 1.7;  // C-
    if (grade >= 67) return 1.3;  // D+
    if (grade >= 65) return 1.0;  // D
    return 0.0;  // F
}

float calculate_gpa(float grades[], int num_subjects) {
    if (num_subjects == 0) return 0.0;
    
    float total_gpa = 0.0;
    for (int i = 0; i < num_subjects; i++) {
        total_gpa += grade_to_gpa(grades[i]);
    }
    return total_gpa / num_subjects;
}

int validate_student_data(Student *student) {
    // Validate ID (positive and reasonable range)
    if (student->id <= 0 || student->id > 999999) {
        printf("Error: Student ID must be between 1 and 999999\n");
        return 0;
    }
    
    // Validate name (not empty, reasonable length)
    if (strlen(student->name) == 0 || strlen(student->name) >= MAX_NAME_LEN) {
        printf("Error: Name must be 1-%d characters\n", MAX_NAME_LEN-1);
        return 0;
    }
    
    // Validate age (reasonable range)
    if (student->age < 16 || student->age > 100) {
        printf("Error: Age must be between 16 and 100\n");
        return 0;
    }
    
    // Validate course name
    if (strlen(student->course) == 0 || strlen(student->course) >= MAX_COURSE_LEN) {
        printf("Error: Course name must be 1-%d characters\n", MAX_COURSE_LEN-1);
        return 0;
    }
    
    // Validate number of subjects
    if (student->num_subjects <= 0 || student->num_subjects > MAX_SUBJECTS) {
        printf("Error: Number of subjects must be 1-%d\n", MAX_SUBJECTS);
        return 0;
    }
    
    // Validate grades (0-100 range)
    for (int i = 0; i < student->num_subjects; i++) {
        if (student->grades[i] < 0.0 || student->grades[i] > 100.0) {
            printf("Error: Grade %d must be between 0.0 and 100.0\n", i+1);
            return 0;
        }
    }
    
    return 1;
}

void print_student(Student *student) {
    printf("\nStudent Details:\n");
    printf("ID: %d\n", student->id);
    printf("Name: %s\n", student->name);
    printf("Age: %d\n", student->age);
    printf("Course: %s\n", student->course);
    printf("Grades: ");
    for (int i = 0; i < student->num_subjects; i++) {
        printf("%.1f ", student->grades[i]);
    }
    printf("\nGPA: %.2f\n", student->gpa);
}

void clear_all_students(StudentDatabase *db) {
    if (!db) return;
    
    char confirm[10];
    printf("\n⚠️  WARNING: This will delete ALL student records!\n");
    printf("Type 'YES' to confirm deletion: ");
    scanf("%s", confirm);
    
    if (strcmp(confirm, "YES") == 0) {
        db->count = 0;
        printf("✅ All student records deleted successfully!\n");
        printf("Database cleared. %d students remaining.\n", db->count);
    } else {
        printf("❌ Operation cancelled. No records deleted.\n");
    }
}