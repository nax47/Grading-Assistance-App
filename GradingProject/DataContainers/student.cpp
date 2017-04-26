#include "student.h"

int Student::idCount = 0;

Student::Student()
{
    ID = idCount;
    idCount += 1;
}

Student::Student(string name)
{
    studentName = name;
    ID = idCount;
    idCount += 1;
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

vector <int> Student::get_LabAssignment_Ids(){

    vector<int> ids;

    for(int i=0; i<gradedLabs.size(); i++){
        ids.push_back(gradedLabs.at(i)->get_Id());
    }

    return ids;
}

vector <LabAssignment *> Student::get_labAssignments(){
    return gradedLabs;
}
