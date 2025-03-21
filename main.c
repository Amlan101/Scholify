#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "database.h"
#include "student.h"
#include "attendance.h"
#include "grades.h"

void show_menu() {
    printf("\n===== Student Database Management System =====\n");
    printf("1. Add Student\n");
    printf("2. View Students\n");
    printf("3. Update Student Details\n");
    printf("4. Delete Student\n");
    printf("5. Mark Attendance\n");
    printf("6. View Attendance\n");
    printf("7. Add Grades\n");
    printf("8. View Grades\n");
    printf("9. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    
    init_database(); 
    
    int choice, student_id;
    char name[100], email[100], date[20], status[10], subject[50], grade[10];

    while (1) {
        show_menu();
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf("Enter Student Name: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0; // Remove newline

                printf("Enter Email: ");
                fgets(email, sizeof(email), stdin);
                email[strcspn(email, "\n")] = 0;

                add_student(name, email);
                break;

            case 2:
                view_students();
                break;

            case 3:  // Update student details
                printf("Enter Student ID: ");
                scanf("%d", &student_id);
                getchar();

                printf("Enter New Name: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0;

                printf("Enter New Email: ");
                fgets(email, sizeof(email), stdin);
                email[strcspn(email, "\n")] = 0;

                update_student(student_id, name, email);
                break;

            case 4:  // Delete student
                printf("Enter Student ID: ");
                scanf("%d", &student_id);
                delete_student(student_id);
                break;

            case 5:
                printf("Enter Student ID: ");
                scanf("%d", &student_id);
                getchar();

                printf("Enter Date (YYYY-MM-DD): ");
                fgets(date, sizeof(date), stdin);
                date[strcspn(date, "\n")] = 0;

                printf("Enter Status (Present/Absent): ");
                fgets(status, sizeof(status), stdin);
                status[strcspn(status, "\n")] = 0;

                add_attendance(student_id, date, status);
                break;

            case 6:
                printf("Enter Student ID: ");
                scanf("%d", &student_id);
                list_attendance(student_id);
                break;

            case 7:
                printf("Enter Student ID: ");
                scanf("%d", &student_id);
                getchar();

                printf("Enter Subject: ");
                fgets(subject, sizeof(subject), stdin);
                subject[strcspn(subject, "\n")] = 0;

                printf("Enter Grade: ");
                fgets(grade, sizeof(grade), stdin);
                grade[strcspn(grade, "\n")] = 0;

                add_grade(student_id, subject, grade);
                break;

            case 8:
                printf("Enter Student ID: ");
                scanf("%d", &student_id);
                list_grades(student_id);
                break;

            case 9:
                printf("Exiting program...\n");
                exit(0);

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}