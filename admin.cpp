#include "admin.h"
#include <fstream>
#include "globalFile.h"
#include <algorithm>

Admin::Admin(){

}

Admin::Admin(string name, string pwd){
    this->m_Name = name;
    this->m_Pwd = pwd;

    this->initVector();

    ifstream ifs;
    ifs.open(COMPUTER_FILE, ios::in);

    ComputerRoom com;
    while(ifs >> com.m_ComId && ifs >> com.m_MaxNum) {
        vCom.push_back(com);
    }

    ifs.close();
    cout << "Total Computer Room: " << vCom.size() << endl;
}

void Admin::operMenu(){
    cout << "================== Welcome ==================" << endl;
    cout << "\t\t 1. Add account" << endl;
    cout << "\t\t 2. Check account" << endl;
    cout << "\t\t 3. Check computer room" << endl;
    cout << "\t\t 4. Delete Reservation" << endl;
    cout << "\t\t 0. Log Out" << endl;
    cout << "Enter a choice: ";
}

void Admin::addPerson(){
    cout << "Enter account type to add: " << endl;
    cout << "1. Add Student" << endl;
    cout << "2. Add Teacher" << endl;

    string fileName;
    string tip;
    string errorTip;
    ofstream ofs;

    int select;
    cin >> select;

    if(select == 1) {
        fileName = STUDENT_FILE;
        tip = "Enter student id: ";
        errorTip = "Student id already exist, enter new id"; 
    }
    else {
        fileName = TEACHER_FILE;
        tip = "Enter teacher id: ";
        errorTip = "Teacher id already exist, enter new id";
    }

    ofs.open(fileName, ios::out | ios::app);

    int id;
    string name;
    string pwd;

    cout << tip << endl;

    while(true) {
        cin >> id;
        bool ret = checkRepeat(id, select);
        if(ret) {
            cout << errorTip << endl;
        }
        else {
            break;
        }
    }

    cout << "Enter name: " << endl;
    cin >> name;
    
    cout << "Enter password: " << endl;
    cin >> pwd;

    ofs << id << " " << name << " " << pwd << endl;
    cout << "Add successfully" << endl;
    system("pause");
    system("cls");
    ofs.close();

    //so that everytime check repeat, will check the latest list
    this->initVector();
}

void printStudent(Student &s) {
    cout << "Id: " << s.m_Id << "\t";
    cout << "Name: " << s.m_Name << endl;
}

void printTeacher(Teacher &t) {
    cout << "Id: " << t.m_EmpId << "\t";
    cout << "Name: " << t.m_Name << endl;
}

void Admin::showPerson(){
    cout << "Please select account type that want to check" << endl;
    cout << "1. Student" << endl;
    cout << "2. Teacher" << endl;
    int select = 0;
    cin >> select;
    if(select == 1) {
        cout << "All student info: " << endl;
        for_each(vStu.begin(), vStu.end(), printStudent);
    }
    else {
        cout << "All teacher info: " << endl;
        for_each(vTea.begin(), vTea.end(), printTeacher);
    }
    system("pause");
    system("cls");
}

void Admin::showComputer(){
    cout << "Computer Room Details: " << endl;

    for(vector<ComputerRoom>::iterator it = vCom.begin(); it != vCom.end(); it++) {
        cout << "Computer Room id: " << it->m_ComId << "\t" << "Maximum Seats:" << it->m_MaxNum << endl;
    }
    system("pause");
    system("cls");
}

void Admin::cleanFile(){
    ofstream ofs(ORDER_FILE, ios::trunc);
    ofs.close();

    cout << "Clear successfully" << endl;
    system("pause");
    system("cls");
}

void Admin::initVector(){
    ifstream ifs;
    ifs.open(STUDENT_FILE, ios::in);
    if(!ifs.is_open()){
        cout << "File not found" << endl;
        return;
    }

    Student s;
    while(ifs >> s.m_Id && ifs >> s.m_Name && ifs >> s.m_Pwd) {
        vStu.push_back(s);
    }

    cout << "The number of students: " << vStu.size() << endl;
    ifs.close();

    ifs.open(TEACHER_FILE, ios::in);
    Teacher t;
    while(ifs >> t.m_EmpId && ifs >> t.m_Name && ifs >> t.m_Pwd) {
        vTea.push_back(t);
    }

    cout << "The number of teachers: " << vStu.size() << endl;
    ifs.close();
}

bool Admin::checkRepeat(int id, int type){
    if(type == 1) {
        for(vector<Student>::iterator it = vStu.begin(); it != vStu.end(); it++) {
            if(id == it->m_Id) {
                return true;
            }
        }
    }
    else {
        for(vector<Teacher>::iterator it = vTea.begin(); it != vTea.end(); it++) {
            if(id == it->m_EmpId) {
                return true;
            }
        }
    }
    return false;
}
