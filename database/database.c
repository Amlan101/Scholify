#include <stdio.h>
#include <sqlite3.h>
#include "database.h"

sqlite3 *db;

// Function to execute SQL commands
int execute_sql(const char *sql) {
    char *err_msg = 0;
    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK) {
        printf("SQL Error: %s\n", err_msg);
        sqlite3_free(err_msg);
        return 1;
    }
    return 0;
}

// Initialize database and create tables
int init_database() {
    int rc = sqlite3_open("students.db", &db);
    if (rc != SQLITE_OK) {
        printf("Cannot open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    // Create Students Table
    const char *students_table = 
        "CREATE TABLE IF NOT EXISTS students ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT NOT NULL, "
        "email TEXT UNIQUE NOT NULL);";

    // Create Attendance Table
    const char *attendance_table = 
        "CREATE TABLE IF NOT EXISTS attendance ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "student_id INTEGER, "
        "date TEXT, "
        "status TEXT, "
        "FOREIGN KEY(student_id) REFERENCES students(id));";

    // Create Grades Table
    const char *grades_table = 
        "CREATE TABLE IF NOT EXISTS grades ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "student_id INTEGER, "
        "subject TEXT, "
        "grade TEXT, "
        "FOREIGN KEY(student_id) REFERENCES students(id));";

    execute_sql(students_table);
    execute_sql(attendance_table);
    execute_sql(grades_table);

    printf("Database initialized successfully!\n");
    return 0;
}
