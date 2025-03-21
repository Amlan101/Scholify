#ifndef ATTENDANCE_H
#define ATTENDANCE_H

// Function to add attendance
int add_attendance(int student_id, const char *date, const char *status);

// Function to list attendance for a specific student
int list_attendance(int student_id);

#endif