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

Lab * Section::get_Lab(int num)
{
    return labList.at(num);
}

