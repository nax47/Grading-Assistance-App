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

    //Setters and getters.
    void set_Name(string name);
    string get_Name();

    void add_Lab(LabAssignment * newLab);
    LabAssignment * get_Lab(int labNum);

    void set_Id(int id);
    int get_Id();

    vector <int> get_LabAssignment_Ids();

    vector <LabAssignment *> get_labAssignments();

    static int idCount;

private:

    string studentName; //student name
    vector <LabAssignment *> gradedLabs; //vector of graded labs
    int ID; //id for database
};



#endif // STUDENT_H
