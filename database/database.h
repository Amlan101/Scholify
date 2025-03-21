#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>

// Function to initialize the database
int init_database();

// Function to execute SQL commands
int execute_sql(const char *sql);

#endif
