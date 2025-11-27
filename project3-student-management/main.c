#include "student_management.h"

void show_menu() {
    printf("\n=== Student Management System ===\n");
    printf("1. Add Student\n");
    printf("2. Display All Students\n");
    printf("3. Search Student by ID\n");
    printf("4. Search Student by Name\n");
    printf("5. Update Student\n");
    printf("6. Delete Student\n");
    printf("7. Sort by GPA\n");
    printf("8. Sort by Name\n");
    printf("9. Generate Reports\n");
    printf("10. Save to File\n");
    printf("11. Load from File\n");
    printf("12. Exit\n");
    printf("================================\n");
    printf("Choose an option: ");
}

Student input_student() {
    Student student = {0};
    
    printf("Enter Student ID: ");
    scanf("%d", &student.id);
    
    printf("Enter Name: ");
    scanf(" %[^\n]", student.name);
    
    printf("Enter Age: ");
    scanf("%d", &student.age);
    
    printf("Enter Course: ");
    scanf(" %[^\n]", student.course);
    
    printf("Enter number of subjects (max %d): ", MAX_SUBJECTS);
    scanf("%d", &student.num_subjects);
    
    if (student.num_subjects > MAX_SUBJECTS) {
        student.num_subjects = MAX_SUBJECTS;
    }
    
    for (int i = 0; i < student.num_subjects; i++) {
        printf("Enter grade for subject %d: ", i + 1);
        scanf("%f", &student.grades[i]);
    }
    
    return student;
}

int main() {
    StudentDatabase *db = init_database();
    if (!db) {
        printf("Failed to initialize database!\n");
        return 1;
    }
    
    int choice;
    Student student;
    Student *found;
    int id;
    char name[MAX_NAME_LEN];
    
    printf("Welcome to Student Management System!\n");
    
    while (1) {
        show_menu();
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                student = input_student();
                if (add_student(db, student)) {
                    printf("Student added successfully!\n");
                } else {
                    printf("Failed to add student. Check for duplicate ID or invalid data.\n");
                }
                break;
                
            case 2:
                display_students(db);
                break;
                
            case 3:
                printf("Enter Student ID: ");
                scanf("%d", &id);
                found = search_by_id(db, id);
                if (found) {
                    print_student(found);
                } else {
                    printf("Student not found!\n");
                }
                break;
                
            case 4:
                printf("Enter Student Name: ");
                scanf(" %[^\n]", name);
                found = search_by_name(db, name);
                if (found) {
                    print_student(found);
                } else {
                    printf("Student not found!\n");
                }
                break;
                
            case 5:
                printf("Enter Student ID to update: ");
                scanf("%d", &id);
                if (search_by_id(db, id)) {
                    student = input_student();
                    student.id = id;
                    if (update_student(db, id, student)) {
                        printf("Student updated successfully!\n");
                    } else {
                        printf("Failed to update student!\n");
                    }
                } else {
                    printf("Student not found!\n");
                }
                break;
                
            case 6:
                printf("Enter Student ID to delete: ");
                scanf("%d", &id);
                if (delete_student(db, id)) {
                    printf("Student deleted successfully!\n");
                } else {
                    printf("Student not found!\n");
                }
                break;
                
            case 7:
                sort_by_gpa(db);
                printf("Students sorted by GPA (descending).\n");
                display_students(db);
                break;
                
            case 8:
                sort_by_name(db);
                printf("Students sorted by name.\n");
                display_students(db);
                break;
                
            case 9:
                printf("\n=== Analytics Report ===\n");
                printf("Total Students: %d\n", db->count);
                printf("Class Average GPA: %.2f\n", calculate_class_average(db));
                generate_course_report(db);
                break;
                
            case 10:
                if (save_to_file(db)) {
                    printf("Data saved successfully!\n");
                } else {
                    printf("Failed to save data!\n");
                }
                break;
                
            case 11:
                if (load_from_file(db)) {
                    printf("Data loaded successfully!\n");
                } else {
                    printf("Failed to load data or file doesn't exist!\n");
                }
                break;
                
            case 12:
                save_to_file(db);
                free_database(db);
                printf("Goodbye!\n");
                return 0;
                
            default:
                printf("Invalid option! Please try again.\n");
        }
    }
}