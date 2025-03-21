#ifndef STUDENT_H
#define STUDENT_H

// Function to add a student
int add_student(const char *name, const char *email);

// Function to list all students
int view_students();

// Function to delete a student
int delete_student(int student_id);

// Function to update a student's details
int update_student(int student_id, const char *new_name, const char *new_email);

#endif