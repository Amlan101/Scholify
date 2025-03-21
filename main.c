#include <stdio.h>
#include "database.h"
#include "student.h"
#include "attendance.h"
#include "grades.h"

int main() {
    // Initialize database
    init_database();

    // Add students
    add_student("Alice", "alice@example.com");
    add_student("Bob", "bob@example.com");

    // View students
    view_students();

    // Mark attendance
    add_attendance(1, "2025-03-21", "Present");
    add_attendance(2, "2025-03-21", "Absent");

    // View attendance records
    list_attendance(1);
    list_attendance(2);

    // Add grades
    add_grade(1, "Math", "A");
    add_grade(1, "Science", "B+");
    add_grade(2, "Math", "C");

    // View grades
    list_grades(1);
    list_grades(2);

    return 0;
}