# 🎓 Computer Room Booking System

A simple **C++ console-based application** that allows **students**, **teachers**, and **administrators** to manage computer room reservations.  
This project demonstrates object-oriented programming, file handling, and role-based access control.

---

## 🚀 Features

### 👩‍🎓 Student Module
Students can:
- Book a computer room  
- View their own bookings  
- View all bookings  
- Cancel their booking  
- Log out  


---

### 👨‍🏫 Teacher Module
Teachers can:
- View all bookings  
- Approve or reject bookings  
- Log out  


---

### 🛠️ Admin Module
Admins can:
- Add accounts  
- Check accounts  
- Check computer rooms  
- Delete reservations  
- Log out  


---

## 📂 Project Structure
```bash
/ComputerRoomBookingSystem
│── main.cpp
│── student.h
│── student.cpp
│── teacher.h
│── teacher.cpp
│── admin.h
│── admin.cpp
│── computerRoom.h
│── orderFile.h
│── globalFile.h
├── students.txt
├── teachers.txt
├── admins.txt
└── orders.txt
```

---

## 🛠️ How to Run

1. Clone the repository:
```bash
git clone https://github.com/yourusername/computer-room-booking-system.git

2. Compile the program:
```bash
g++ *.cpp -o bookingSystem

3. Run:
```bash
./bookingSystem



