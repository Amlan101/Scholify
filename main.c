#include <stdio.h>
#include "database.h"
#include "student.h"

int main() {
    // Initialize database
    init_database();

    // Test adding students
    add_student("Amlan", "amlan@gmail.com");
    add_student("Tony", "Tony@gmail.com");

    // View students
    view_students();

    // Update a student's details
    update_student(1, "Amlan Prasad Sahoo", "workforamlan@gmail.com");

    // View students after update
    view_students();

    // Delete a student
    delete_student(2);

    // View students after deletion
    view_students();

    return 0;
}
