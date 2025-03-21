#include <stdio.h>
#include <sqlite3.h>
#include "attendance.h"
#include "database.h"

// Function to mark attendance
int add_attendance(int student_id, const char *date, const char *status) {
    char sql[256];
    snprintf(sql, sizeof(sql),
             "INSERT INTO attendance (student_id, date, status) VALUES (%d, '%s', '%s');",
             student_id, date, status);

    if (execute_sql(sql) == 0) {
        printf("Attendance marked for student ID %d on %s as %s.\n", student_id, date, status);
        return 0;
    } else {
        printf("Failed to mark attendance.\n");
        return 1;
    }
}

// Function to fetch student details and display attendance
int list_attendance(int student_id) {
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

    // Display attendance
    snprintf(sql, sizeof(sql),
             "SELECT date, status FROM attendance WHERE student_id = %d;", student_id);

    printf("\n===== Attendance Records =====\n%s\n", student_info);
    printf("%-15s | %-10s\n", "Date", "Status");
    printf("-------------------------------\n");

    int attendance_callback(void *NotUsed, int argc, char **argv, char **colNames) {
        printf("%-15s | %-10s\n", argv[0], argv[1]);
        return 0;
    }

    if (sqlite3_exec(db, sql, attendance_callback, 0, &err_msg) != SQLITE_OK) {
        printf("Error retrieving attendance: %s\n", err_msg);
        sqlite3_free(err_msg);
        return 1;
    }

    return 0;
}
