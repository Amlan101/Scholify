#include <stdio.h>
#include "database.h"

int main() {
    if (init_database() != 0) {
        return 1;
    }
    printf("Welcome to the Student Management System!\n");
    return 0;
}
