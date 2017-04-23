#include "student.h"

Student::Student()
{

}

Student::Student(string name)
{
    studentName = name;
}

Student::~Student()
{

}

void Student::set_Name(string name)
{
    studentName = name;
}

string Student::get_Name()
{
    return studentName;
}

void Student::add_Lab(LabAssignment *newLab)
{
    gradedLabs.push_back(newLab);
}

LabAssignment * Student::get_Lab(int labNum)
{
    return gradedLabs.at(labNum);
}

void Student::set_Id(int id)
{
    ID = id;
}

int Student::get_Id()
{
    return ID;
}
