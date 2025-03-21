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

// Callback function to print attendance records
int attendance_callback(void *NotUsed, int argc, char **argv, char **colNames) {
    for (int i = 0; i < argc; i++) {
        printf("%s: %s\n", colNames[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

// Function to view attendance of a specific student
int list_attendance(int student_id) {
    char sql[256];
    snprintf(sql, sizeof(sql),
             "SELECT date, status FROM attendance WHERE student_id = %d;", student_id);

    printf("\nAttendance Records for Student ID %d:\n", student_id);

    char *err_msg = 0;
    int rc = sqlite3_exec(db, sql, attendance_callback, 0, &err_msg);

    if (rc != SQLITE_OK) {
        printf("Error retrieving attendance: %s\n", err_msg);
        sqlite3_free(err_msg);
        return 1;
    }

    return 0;
}