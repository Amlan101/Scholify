import smtplib
import os
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart
import sys
from dotenv import load_dotenv

load_dotenv()

# SMTP Configuration
SMTP_SERVER = os.getenv("SMTP_SERVER")
SMTP_PORT = int(os.getenv("SMTP_PORT"))
SENDER_EMAIL = os.getenv("SCHOLIFY_EMAIL")
SENDER_PASSWORD = os.getenv("SCHOLIFY_PASSWORD")

def send_email(receiver_email, student_name, attendance, grades):
    subject = f"Student Report for {student_name}"
    body = f"""
    Hello {student_name},

    Your Attendance: {attendance}%
    Your Grades:
    {grades}

    Best Regards,
    Scholify Team
    """

    msg = MIMEMultipart()
    msg['From'] = SENDER_EMAIL
    msg['To'] = receiver_email
    msg['Subject'] = subject
    msg.attach(MIMEText(body, 'plain'))

    try:
        server = smtplib.SMTP(SMTP_SERVER, SMTP_PORT)
        server.starttls()
        server.login(SENDER_EMAIL, SENDER_PASSWORD)
        server.sendmail(SENDER_EMAIL, receiver_email, msg.as_string())
        server.quit()
        print("Email sent successfully!")
    except Exception as e:
        print(f"Error sending email: {e}")

if __name__ == "__main__":
    if len(sys.argv) < 4:
        print("Usage: python send_email.py <receiver_email> <student_name> <attendance> <grades>")
        sys.exit(1)

    receiver_email = sys.argv[1]
    student_name = sys.argv[2]
    attendance = sys.argv[3]
    grades = " ".join(sys.argv[4:])  

    send_email(receiver_email, student_name, attendance, grades)
