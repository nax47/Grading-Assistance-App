#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>
#include <vector>
#include "labassignment.h"

using namespace std;

class LabAssignment;

class Student
{
public:

    Student();
    Student(string name);
    ~Student();


    void set_Name(string name);
    string get_Name();

    void add_Lab(LabAssignment * newLab);
    LabAssignment * get_Lab(int labNum);

private:

    string studentName;
    vector <LabAssignment *> gradedLabs;

};

#endif // STUDENT_H
