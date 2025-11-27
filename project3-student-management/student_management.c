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

void generate_course_report(StudentDatabase *db) {
    printf("\n=== Course Report ===\n");
    
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
        printf("Course: %-15s Average GPA: %.2f Students: %d\n",
               courses[i], course_totals[i] / course_counts[i], course_counts[i]);
    }
}

float calculate_gpa(float grades[], int num_subjects) {
    if (num_subjects == 0) return 0.0;
    
    float total = 0.0;
    for (int i = 0; i < num_subjects; i++) {
        total += grades[i];
    }
    return total / num_subjects;
}

int validate_student_data(Student *student) {
    return student->id > 0 && 
           strlen(student->name) > 0 && 
           student->age > 0 && student->age < 150 &&
           student->num_subjects > 0 && student->num_subjects <= MAX_SUBJECTS;
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