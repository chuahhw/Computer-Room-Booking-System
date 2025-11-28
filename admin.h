#pragma once
#include <iostream>
using namespace std;
#include "Identity.h"
#include <vector>
#include "student.h"
#include "teacher.h"
#include "computerRoom.h"

class Admin: public Identity{
    public:
    Admin();

    Admin(string name, string pwd);

    virtual void operMenu();

    void addPerson();

    void showPerson();

    void showComputer();

    void cleanFile();

    void initVector();

    bool checkRepeat(int id, int type);

    vector<Student>vStu;

    vector<Teacher>vTea;

    vector<ComputerRoom>vCom;
};