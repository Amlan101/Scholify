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

// Callback function to print grade records
int grades_callback(void *NotUsed, int argc, char **argv, char **colNames) {
    for (int i = 0; i < argc; i++) {
        printf("%s: %s\n", colNames[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

// Function to view grades of a specific student
int list_grades(int student_id) {
    char sql[256];
    snprintf(sql, sizeof(sql),
             "SELECT subject, grade FROM grades WHERE student_id = %d;", student_id);

    printf("\nGrades for Student ID %d:\n", student_id);

    char *err_msg = 0;
    int rc = sqlite3_exec(db, sql, grades_callback, 0, &err_msg);

    if (rc != SQLITE_OK) {
        printf("Error retrieving grades: %s\n", err_msg);
        sqlite3_free(err_msg);
        return 1;
    }

    return 0;
}