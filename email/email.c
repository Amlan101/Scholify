#include <stdio.h>
#include <stdlib.h>
#include "email.h"

#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>
#include "database.h"

int send_student_report(int student_id) {
    char sql[256];
    sqlite3_stmt *stmt;
    char email[100], name[100], attendance[10], grades[500] = "";

    // Fetch Student Name & Email
    snprintf(sql, sizeof(sql), "SELECT name, email FROM students WHERE id = %d;", student_id);
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) == SQLITE_OK && sqlite3_step(stmt) == SQLITE_ROW) {
        strcpy(name, (const char*)sqlite3_column_text(stmt, 0));
        strcpy(email, (const char*)sqlite3_column_text(stmt, 1));
    } else {
        printf("Student ID %d not found!\n", student_id);
        sqlite3_finalize(stmt);
        return 1;
    }
    sqlite3_finalize(stmt);

    // Fetch Attendance Percentage
    snprintf(sql, sizeof(sql),
             "SELECT COUNT(*) FROM attendance WHERE student_id = %d AND status='Present';", student_id);
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) == SQLITE_OK && sqlite3_step(stmt) == SQLITE_ROW) {
        snprintf(attendance, sizeof(attendance), "%d", sqlite3_column_int(stmt, 0));
    } else {
        strcpy(attendance, "N/A");
    }
    sqlite3_finalize(stmt);

    // Fetch Grades (Concatenating all subjects with newlines)
    snprintf(sql, sizeof(sql), "SELECT subject, grade FROM grades WHERE student_id = %d;", student_id);
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            char temp[100];
            snprintf(temp, sizeof(temp), "%s: %s\n", sqlite3_column_text(stmt, 0), sqlite3_column_text(stmt, 1));
            strcat(grades, temp);
        }
    } else {
        strcpy(grades, "No Grades Available");
    }
    sqlite3_finalize(stmt);

    // Construct and Call Python Script
    char command[1024];
    snprintf(command, sizeof(command),
             "python send_email.py \"%s\" \"%s\" \"%s\" \"%s\"",
             email, name, attendance, grades);
    
    printf("Sending report to %s (%s)...\n", name, email);
    int result = system(command);

    return result == 0 ? 0 : 1;
}