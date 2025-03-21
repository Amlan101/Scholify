#include <stdio.h>
#include <sqlite3.h>
#include "grades.h"
#include "database.h"

// Function to add a grade
int add_grade(int student_id, const char *subject, const char *grade) {
    char sql[256];
    snprintf(sql, sizeof(sql),
             "INSERT INTO grades (student_id, subject, grade) VALUES (%d, '%s', '%s');",
             student_id, subject, grade);

    if (execute_sql(sql) == 0) {
        printf("Grade added for student ID %d: %s - %s\n", student_id, subject, grade);
        return 0;
    } else {
        printf("Failed to add grade.\n");
        return 1;
    }
}

// Function to fetch student details and display grades
int list_grades(int student_id) {
    char sql[256];
    char student_info[256] = {0};
    char *err_msg = 0;

    // Fetch student details
    snprintf(sql, sizeof(sql),
             "SELECT name, email FROM students WHERE id = %d;", student_id);

    int callback(void *data, int argc, char **argv, char **colNames) {
        snprintf(student_info, sizeof(student_info), "Student: %s (%s)", argv[0], argv[1]);
        return 0;
    }

    if (sqlite3_exec(db, sql, callback, 0, &err_msg) != SQLITE_OK) {
        printf("Error retrieving student details: %s\n", err_msg);
        sqlite3_free(err_msg);
        return 1;
    }

    // Display grades
    snprintf(sql, sizeof(sql),
             "SELECT subject, grade FROM grades WHERE student_id = %d;", student_id);

    printf("\n===== Grades =====\n%s\n", student_info);
    printf("%-20s | %-5s\n", "Subject", "Grade");
    printf("----------------------------\n");

    int grades_callback(void *NotUsed, int argc, char **argv, char **colNames) {
        printf("%-20s | %-5s\n", argv[0], argv[1]);
        return 0;
    }

    if (sqlite3_exec(db, sql, grades_callback, 0, &err_msg) != SQLITE_OK) {
        printf("Error retrieving grades: %s\n", err_msg);
        sqlite3_free(err_msg);
        return 1;
    }

    return 0;
}