#include <stdio.h>
#include <sqlite3.h>
#include <string.h>
#include "student.h"
#include "database.h"

// Function to add a student
int add_student(const char *name, const char *email) {
    char sql[256];
    snprintf(sql, sizeof(sql),
             "INSERT INTO students (name, email) VALUES ('%s', '%s');",
             name, email);

    return execute_sql(sql) == 0 ? printf("Student '%s' added successfully!\n", name), 0 : printf("Failed to add student.\n"), 1;
}

// Callback function to print student data
int student_callback(void *NotUsed, int argc, char **argv, char **colNames) {
    for (int i = 0; i < argc; i++) {
        printf("%s: %s\n", colNames[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

// Function to fetch and display all students
int view_students() {
    printf("\nList of Students:\n");
    return sqlite3_exec(db, "SELECT * FROM students;", student_callback, 0, NULL);
}

// Function to delete a student by ID
int delete_student(int student_id) {
    char sql[256];

    // First, delete attendance and grades linked to this student
    snprintf(sql, sizeof(sql), "DELETE FROM attendance WHERE student_id = %d;", student_id);
    execute_sql(sql);

    snprintf(sql, sizeof(sql), "DELETE FROM grades WHERE student_id = %d;", student_id);
    execute_sql(sql);

    // Now, delete the student record
    snprintf(sql, sizeof(sql), "DELETE FROM students WHERE id = %d;", student_id);

    if (execute_sql(sql) == 0) {
        printf("Student with ID %d deleted successfully!\n", student_id);
        return 0;
    } else {
        printf("Failed to delete student.\n");
        return 1;
    }
}

// Function to update student details
int update_student(int student_id, const char *new_name, const char *new_email) {
    char sql[256];
    snprintf(sql, sizeof(sql),
             "UPDATE students SET name = '%s', email = '%s' WHERE id = %d;",
             new_name, new_email, student_id);

    if (execute_sql(sql) == 0) {
        printf("Student with ID %d updated successfully!\n", student_id);
        return 0;
    } else {
        printf("Failed to update student.\n");
        return 1;
    }
}

