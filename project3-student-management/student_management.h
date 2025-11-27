#ifndef STUDENT_MANAGEMENT_H
#define STUDENT_MANAGEMENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 50
#define MAX_COURSE_LEN 30
#define MAX_SUBJECTS 5
#define DATA_FILE "students.dat"

typedef struct {
    int id;
    char name[MAX_NAME_LEN];
    int age;
    char course[MAX_COURSE_LEN];
    float grades[MAX_SUBJECTS];
    int num_subjects;
    float gpa;
} Student;

typedef struct {
    Student *students;
    int count;
    int capacity;
} StudentDatabase;

// Core functions
StudentDatabase* init_database();
void free_database(StudentDatabase *db);
int add_student(StudentDatabase *db, Student student);
int update_student(StudentDatabase *db, int id, Student updated);
int delete_student(StudentDatabase *db, int id);
void display_students(StudentDatabase *db);
Student* search_by_id(StudentDatabase *db, int id);
Student* search_by_name(StudentDatabase *db, const char *name);

// File operations
int save_to_file(StudentDatabase *db);
int load_from_file(StudentDatabase *db);

// Sorting and analytics
void sort_by_gpa(StudentDatabase *db);
void sort_by_name(StudentDatabase *db);
void sort_by_id(StudentDatabase *db);
float calculate_class_average(StudentDatabase *db);
float calculate_median_gpa(StudentDatabase *db);
Student* find_highest_gpa(StudentDatabase *db);
Student* find_lowest_gpa(StudentDatabase *db);
Student* get_top_students(StudentDatabase *db, int n);
Student* get_top_student_by_course(StudentDatabase *db, const char *course);
void generate_course_report(StudentDatabase *db);
void display_top_n_students(StudentDatabase *db, int n);
int binary_search_by_id(StudentDatabase *db, int id);

// Utility functions
float grade_to_gpa(float grade);
float calculate_gpa(float grades[], int num_subjects);
int validate_student_data(Student *student);
void print_student(Student *student);
void clear_all_students(StudentDatabase *db);

#endif