#include "section.h"

int Section::idCount = 0;

Section::Section()
{
    ID = idCount;
    idCount += 1;
}

Section::~Section()
{

}

void Section::add_Student(Student *stu)
{
    studentList.push_back(stu);
}

int Section::get_Student_Size()
{
    return studentList.size();
}

string Section::get_Student_Name(int num)
{
    Student * tmp;
    tmp = studentList.at(num);
    return tmp->get_Name();
}

Student * Section::get_Student(string name)
{
    Student * tmpPtr;
    for(int i =0; i < studentList.size(); i++)
    {
        tmpPtr = studentList.at(i);
        if(tmpPtr->get_Name() == name)
        {
            return studentList.at(i);
        }
    }
}

void Section::set_Id(int id)
{
    ID = id;
}

int Section::get_Id()
{
    return ID;
}

void Section::add_Lab(Lab *newLab)
{
    labList.push_back(newLab);
}

int Section::get_Lab_Size()
{
    return labList.size();
}

Lab * Section::get_Lab(int num)
{
    return labList.at(num);
}

vector <int> Section::get_Student_Ids(){

    vector<int> ids;

    for(int i=0; i<studentList.size(); i++){
        ids.push_back(studentList.at(i)->get_Id());
    }

    return ids;
}

vector <int> Section::get_Lab_Ids(){

    vector<int> ids;

    for(int i=0; i<labList.size(); i++){
        ids.push_back(labList.at(i)->get_Id());
    }

    return ids;
}

vector <Student *> Section::get_students(){
    return studentList;
}

vector <Lab *> Section::get_labs(){
    return labList;
}

