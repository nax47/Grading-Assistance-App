#include "section.h"

Section::Section()
{

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

