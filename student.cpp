#include "student.h"
#include <string>
#include <fstream>
#include "globalFile.h"
#include "orderFile.h"

Student::Student(){

}

Student::Student(int id, string name, string pwd) {
    this->m_Id = id;
    this->m_Name = name;
    this->m_Pwd = pwd;

    ifstream ifs;
    ifs.open(COMPUTER_FILE, ios::in);

    ComputerRoom com;
    while(ifs >> com.m_ComId && ifs >> com.m_MaxNum) {
        vCom.push_back(com);
    }

    ifs.close();
}


void Student::operMenu(){
    cout << "================== Welcome ==================" << endl;
    cout << "\t\t 1. Book Room" << endl;
    cout << "\t\t 2. View My Bookings" << endl;
    cout << "\t\t 3. View All Bookings" << endl;
    cout << "\t\t 4. Cancel Booking" << endl;
    cout << "\t\t 0. Log Out" << endl;
    cout << "Enter a choice: " << endl;
}

void Student::applyOrder() {
    cout << "Computer Room Open Hour: Monday to Friday" << endl;
    cout << "Enter the day: " << endl;
    cout << "1. Monday" << endl;
    cout << "2. Tuesday" << endl;
    cout << "3. Wednesday" << endl;
    cout << "4. Thrusday" << endl;
    cout << "5. Friday" << endl;

    int date = 0;
    int interval = 0;
    int room = 0;

    while(true) {
        cin >> date;
        if(date >= 1 && date <= 5) {
            break;
        }
        cout << "Invalid day, please enter the day again" << endl;
    }

    cout << "Enter the time: " << endl;
    cout << "1. Morning" << endl;
    cout << "2. Afternoon" << endl;

    while(true) {
        cin >> interval;
        if(interval >= 1 && interval <= 2) {
            break;
        }
        cout << "Invalid time, please enter the day again" << endl;
    }

    cout << "Please choose computer room: " << endl;
    for(int i = 0; i < vCom.size(); i++) {
        cout << vCom[i].m_ComId << " room capacity is " << vCom[i].m_MaxNum << " seats." << endl;
    }

    while(true) {
        cin >> room;
        if(room >= 1 && room <= 3) {
            break;
        }
        cout << "Invalid room, enter room again" << endl;
    }

    cout << "Reserve success" << endl;

    ofstream ofs;
    ofs.open(ORDER_FILE, ios::app);

    ofs << "date:" << date << " ";
    ofs << "interval:" << interval << " ";
    ofs << "stuId:" << this->m_Id << " ";
    ofs << "stuName:" << this->m_Name << " ";
    ofs << "roomId:" << room << " ";
    ofs << "status:" << 1 << endl;

    ofs.close();
    system("pause");
    system("cls");
}

void Student::showMyOrder() {
     OrderFile of;
     if(of.m_Size == 0) {
        cout << "No order" << endl;
        system("pause");
        system("cls");
        return;
     }

     for(int i = 0; i < of.m_Size; i++) {
        // .c_str() to change to const char *
        if(this->m_Id == atoi(of.m_orderData[i]["stuId"].c_str())) {
            cout << "Reserve day: " << of.m_orderData[i]["date"] << "\t";
            cout << "Reserve time: " << (of.m_orderData[i]["interval"] == "1" ? "Morning" : "Afternoon") << "\t";
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
            else {
                status += "reserve cancel";
            }
            cout << status << endl;
        }
     }
     system("pause");
     system("cls");
}

void Student::showAllOrder() {
    OrderFile of;
    if(of.m_Size == 0) {
        cout << "no booking" << endl;
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

void Student::cancelOrder() {
    OrderFile of;
    if(of.m_Size == 0) {
        cout << "No record" << endl;
        system("pause");
        system("cls");
        return;
    }

    cout << "Enter cancel order id: " << endl;
    vector<int>v;
    int index = 1;
    for(int i = 0; i < of.m_Size; i++) {
        if(this->m_Id == atoi(of.m_orderData[i]["stuId"].c_str())){
            if(of.m_orderData[i]["status"] == "1" || of.m_orderData[i]["status"] == "2"){
                v.push_back(i);
                cout << index++ << ",";
                cout << "Reserve day: " << of.m_orderData[i]["date"] << "\t";
                cout << "Time: " << (of.m_orderData[i]["interval"] == "1"? "morning" : "afternoon") << "\t";
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
                else {
                    status += "reserve cancel";
                }
                cout << status << endl;
            }
        }
    }

    cout << "Press 0 to go back, other number to continue cancel booking" << endl;
    int select = 0;
    while(true) {
        cin >> select;

        if(select >= 0 && select <= v.size()) {
            if(select == 0) {
                break;
            }
            else {
                of.m_orderData[v[select - 1]]["status"] = "0";
                of.updateOrder();
                cout << "Cancel booking successfully" << endl;
                break;
            }
        }
        cout << "invalid" << endl;
    }
    system("pause");
    system("cls");
}