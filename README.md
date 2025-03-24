# **Scholify - Student Database Management System** 🎓  

**Scholify** is a **C-based Student Management System** integrated with an SQLite database and an **automated email notification system**. The system allows administrators to manage students, track attendance, record grades, and send performance reports via email.  

## **📜 Features**
✅ **Student Management:** Add, update, delete, and view student records  
✅ **Attendance Tracking:** Mark attendance and view attendance records  
✅ **Grades Management:** Add and view student grades  
✅ **Email Notifications:** Automatically send student reports via email  
✅ **SQLite Integration:** Stores all data persistently using SQLite  

---

## **📁 Project Structure**
```
Scholify/
│── database/
│   ├── database.c
│   ├── database.h
│── student/
│   ├── student.c
│   ├── student.h
│── attendance/
│   ├── attendance.c
│   ├── attendance.h
│── grades/
│   ├── grades.c
│   ├── grades.h
│── email/
│   ├── email.c
│   ├── email.h
│── send_email.py
│── main.c
│── Makefile
│── .env
│── README.md
│── .gitignore
```
- **C files** handle database operations, student records, attendance, and grades.  
- **`send_email.py`** handles sending automated emails. 
---

## **💻 Installation & Setup**
### **1️⃣ Clone the Repository**
```bash
git clone https://github.com/Amlan101/Scholify.git
cd Scholify
```

### **2️⃣ Install Dependencies**
- Install **SQLite3**:
  ```bash
  sudo apt install sqlite3 libsqlite3-dev  # Linux
  ```
  or  
  Download **SQLite** from [SQLite Official Page](https://www.sqlite.org/download.html) for Windows.  

- Install Python dependencies:
  ```bash
  pip install -r requirements.txt
  ```

### **3️⃣ Set Up Environment Variables**
Create a `.env` file in the project root:
```ini
SMTP_SERVER=smtp.gmail.com
SMTP_PORT=587
SCHOLIFY_EMAIL=your_email@gmail.com
SCHOLIFY_PASSWORD=your_app_password
```
⚠️ **Use an App Password instead of your Gmail password.** Generate one from [Google App Passwords](https://myaccount.google.com/apppasswords).

---

## **⚙️ Compilation & Running**
### **🔹 Compile the Project**
Run the following command to compile the project:
```bash
gcc main.c database/database.c student/student.c attendance/attendance.c grades/grades.c email/email.c -I"./database" -I"./student" -I"./attendance" -I"./grades" -I"./email" -I"/path/to/sqlite" -L"/path/to/sqlite" -lsqlite3 -o scholify
```
For **Windows**, replace `/path/to/sqlite` with your SQLite installation path.

### **🔹 Run the Program**
```bash
./scholify
```

---

## **📧 Sending Email Reports**
To send an email report to a student using the Python script:
```bash
python send_email.py <student_email> <student_name> <attendance_percentage>,<grades>
```
Example:
```bash
python send_email.py tonystark@gmail.com "Tony Stark" 85,"A"
```

### **🔥 Automate Email Sending from C**
To send emails directly from the C program:
```c
system("python send_email.py tonystark@gmail.com "Tony Stark" 85,"A"");
```

---

## **📜 License**
This project is licensed under the **MIT License**. Feel free to use and modify.

---

## **🌟 Contribution**
Want to improve **Scholify**? Contributions are welcome!  
1. Fork the repository  
2. Create a new branch (`git checkout -b feature-branch`)  
3. Commit changes (`git commit -m "Added a feature"`)  
4. Push to GitHub (`git push origin feature-branch`)  
5. Open a pull request  
