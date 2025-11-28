#include "teacher.h"
#include <vector>

Teacher::Teacher(){

}

Teacher::Teacher(int empId, string name, string pwd){
    this->m_EmpId = empId;
    this->m_Name = name;
    this->m_Pwd = pwd;
}

void Teacher::operMenu(){
    cout << "================== Welcome ==================" << endl;
    cout << "\t\t 1. View All Bookings" << endl;
    cout << "\t\t 2. Approve Booking" << endl;
    cout << "\t\t 0. Log Out" << endl;
    cout << "Enter a choice: " << endl;
}

void Teacher::showAllOrder(){
    OrderFile of;
    if(of.m_Size == 0){
        cout << "No booking" << endl;
        system("pause");
        system("cls");
        return;
    }

    for(int i = 0; i < of.m_Size; i++) {
        cout << i + 1 << ": ";
        cout << "Reserve day: " << of.m_orderData[i]["date"] << "\t";
        cout << "Reserve time: " << (of.m_orderData[i]["interval"] == "1" ? "Morning" : "Afternoon") << "\t";
        cout << "Student id: " << of.m_orderData[i]["stuId"] << "\t";
        cout << "Student name: " << of.m_orderData[i]["stuName"] << "\t";
        cout << "Computer room id: " << of.m_orderData[i]["roomId"] << "\t";
        string status = "Status: ";
        if(of.m_orderData[i]["status"] == "1") {
            status += "waiting approval";
        }
        else if(of.m_orderData[i]["status"] == "2") {
            status += "reserve success";
        }
        else if(of.m_orderData[i]["status"] == "3") {
            status += "reserve unsuccessful, not approved";
        }
        else{
            status += "reserve cancel";
        }
        cout << status << endl;
    }
    system("pause");
    system("cls");
}

void Teacher::validOrder(){
    OrderFile of;
    if(of.m_Size == 0) {
        cout << "No order" << endl;
        system("pause");
        system("cls");
        return;
    }

    vector<int>v;
    int index = 0;
    cout << "Order that need to approve:" << endl;
    for(int i = 0; i < of.m_Size; i++) {
        if(of.m_orderData[i]["status"] == "1") {
            v.push_back(i);
            cout << ++index << ": ";
            cout << "Reserve day: " << of.m_orderData[i]["date"] << "\t";
            cout << "Reserve time: " << (of.m_orderData[i]["interval"] == "1" ? "Morning" : "Afternoon") << "\t";
            cout << "Student id: " << of.m_orderData[i]["stuId"] << "\t";
            cout << "Student name: " << of.m_orderData[i]["stuName"] << "\t";
            cout << "Computer room id: " << of.m_orderData[i]["roomId"] << "\t";
            string status = "Status: Waiting for approval";
            cout << status << endl;
        }
    }
    cout << "Enter the order id that want to approve, 0 to go back" << endl;
    int select = 0;
    int ret = 0;

    while(true) {
        cin >> select;
        if(select >= 0 && select <= v.size()) {
            if(select == 0) {
                break;
            }
            else {
                cout << "Enter the choice: " << endl;
                cout << "1. Approve" << endl;
                cout << "2. Reject" << endl;
                cin >> ret;
                if(ret == 1) {
                    of.m_orderData[v[select - 1]]["status"] = "2";
                }
                else {
                    of.m_orderData[v[select - 1]]["status"] = "-1";
                }
                of.updateOrder();
                cout << "Approve finish" << endl;
                break;
            }
        }
        cout << "Invalid choice" << endl;
    }
    system("pause");
    system("cls");
}
