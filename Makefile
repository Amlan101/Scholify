# Compiler
CC = gcc

# Compiler flags
CFLAGS = -I"C:/Users/Amlan/sqlite" -I"./database" -I"./attendance" -I"./grades" -I"./email"
LDFLAGS = C:/Users/Amlan/sqlite/sqlite3.o

# Source files
SRC = main.c database/database.c attendance/attendance.c grades/grades.c email/email.c

# Object files
OBJ = $(SRC:.c=.o)

# Target executable
TARGET = scholify.exe

# Default rule
all: $(TARGET)

# Linking the final executable
$(TARGET): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $(TARGET)

# Compiling C files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule to delete compiled files
clean:
	del /Q *.o $(TARGET)
