#include <iostream>
using namespace std;
#include "Identity.h"
#include <fstream>
#include "globalFile.h"
#include "student.h"
#include "teacher.h"
#include "admin.h"

//g++ bookingsystem.cpp student.cpp teacher.cpp admin.cpp orderFile.cpp -o bookingsystem.exe
void studentMenu(Identity * &student) {
    while(true) {
        student->operMenu();
        Student * stu = (Student *)student;
        int select = 0;
        cin >> select;

        if(select == 1) {
            stu->applyOrder();
        }
        else if(select == 2) {
            stu->showMyOrder();
        }
        else if(select == 3){
            stu->showAllOrder();
        }
        else if(select == 4) {
            stu->cancelOrder();
        }
        else if(select == 0) {
            delete student;
            cout << "Log out" << endl;
            system("pause");
            system("cls");
            return;
        }
        else {
            cout << "Invalid choice" << endl;
            system("pause");
            system("cls");
        }
    }
}

void adminMenu(Identity * &admin) {
    while(true) {
        admin->operMenu();
        Admin *a = (Admin*)admin;

        int select = 0;
        cin >> select;

        if(select == 1) {
            cout << "Add account" << endl;
            a->addPerson();
        }
        else if(select == 2) {
            cout << "Check account" << endl;
            a->showPerson();
        }
        else if(select == 3) {
            cout << "Check computer room" << endl;
            a->showComputer();
        }
        else if(select == 4) {
            cout << "Delete Reservation" << endl;
            a->cleanFile();
        }
        else if(select == 0) {
            cout << "Log Out" << endl;
            system("pause");
            system("cls");
            return;
        }
        else {
            cout << "Invalid choice" << endl;
            system("pause");
            system("cls");
        }
    }
}

void teacherMenu(Identity * &teacher) {
    while(true) {
        teacher->operMenu();
        Teacher * tea = (Teacher*)teacher;
        int select = 0;
        cin >> select;
        if(select == 1) {
            tea->showAllOrder();
        }
        else if(select == 2) {
            tea->validOrder();
        }
        else if(select == 0) {
            delete teacher;
            cout << "Log out" << endl;
            system("pause");
            system("cls");
            return;
        }
        else {
            cout << "Invalid choice" << endl;
            system("pause");
            system("cls");
        }
    }
}

void LoginIn(string fileName, int type) {
    Identity *person = NULL;

    ifstream ifs;
    ifs.open(fileName, ios::in);

    if(!ifs.is_open()) {
        cout << "The file is not available" << endl;
        ifs.close();
        return;
    }

    int id = 0;
    string name;
    string pwd;

    if(type == 1) {
        cout << "Please enter student id: " << endl;
        cin >> id;
    }
    else if(type == 2) {
        cout << "Please enter employee id: " << endl;
        cin >> id;
    }

    cout << "Please enter name: " << endl;
    cin >> name;

    cout << "Please enter password: " << endl;
    cin >> pwd;

    if(type == 1) {
        int fId;
        string fName;
        string fPwd;
        while(ifs >> fId && ifs >> fName && ifs >> fPwd)
        {
            if(fId == id && fName == name && fPwd == pwd)
            {
                cout << "Log in success" << endl;
                system("pause");
                system("cls");
                person = new Student(id, name, pwd);
                studentMenu(person);
                return;
            }
        }
    }
    else if(type == 2) {
        int fId;
        string fName;
        string fPwd;
        while(ifs >> fId && ifs >> fName && ifs >> fPwd)
        {
            if(fId == id && fName == name && fPwd == pwd)
            {
                cout << "Log in success" << endl;
                system("pause");
                system("cls");
                person = new Teacher(id, name, pwd);
                teacherMenu(person);
                return;
            }
        }
    }
    else if(type == 3) {
        string fName;
        string fPwd;
        while(ifs >> fName && ifs >> fPwd)
        {
            if(fName == name && fPwd == pwd)
            {
                cout << "Log in success" << endl;
                system("pause");
                system("cls");
                person = new Admin(name, pwd);
                adminMenu(person);
                return;
            }
        }
    }
    cout << "Invalid login" << endl;
    system("pause");
    system("cls");
}

int main() {
    int select = 0;
    while(true) {
        cout << "================== Welcome ==================" << endl;
        cout << endl << "Choose your position: " << endl;
        cout << "\t\t 1. Student" << endl;
        cout << "\t\t 2. Teacher" << endl;
        cout << "\t\t 3. Admin" << endl;
        cout << "\t\t 0. Exit" << endl;
        cout << "Enter a choice: ";
        cin >> select;

        switch(select) {
            case 0:
                cout << "Goodbye!" << endl;
                system("pause");
                return 0;
            case 1: 
                LoginIn(STUDENT_FILE, 1);
                break;
            case 2:
                LoginIn(TEACHER_FILE, 2);
                break;
            case 3:
                LoginIn(ADMIN_FILE, 3);
                break;
            default:
                cout << "Choice invalid, please enter again." << endl;
                break;
        }
        system("pause");
        system("cls");
    }
    return 0;
}