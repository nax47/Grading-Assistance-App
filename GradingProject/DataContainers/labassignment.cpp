#include "labassignment.h"

LabAssignment::LabAssignment()
{

}

LabAssignment::~LabAssignment()
{

}

void LabAssignment::set_Student(Student *kid)
{
    student = kid;
}

Student * LabAssignment::get_Student()
{
    return student;
}

void LabAssignment::new_RI(RubricItem *RIptr)
{
    appliedItems.push_back(RIptr);
}

RubricItem * LabAssignment::get_RI(string subject)
{
    RubricItem * tmpPtr;
    for(int i =0; i < appliedItems.size(); i++)
    {
        tmpPtr = appliedItems.at(i);
        if(tmpPtr->get_Subject() == subject)
        {
            return appliedItems.at(i);
        }
    }
    return nullptr;
}

void LabAssignment::add_Comment(Comment *com, RubricItem *item)
{
    RubricItem * tmpPtr;
    for(int i =0; i < appliedItems.size(); i++)
    {
        tmpPtr = appliedItems.at(i);
        if(tmpPtr == item)
        {
            tmpPtr->add_Comment(com);
            return;
        }
    }
}

Comment * LabAssignment::get_Comment(RubricItem *item, int num)
{
    RubricItem * tmpPtr;
    for(int i =0; i < appliedItems.size(); i++)
    {
        tmpPtr = appliedItems.at(i);
        if(tmpPtr == item)
        {
            return tmpPtr->get_Comment(num);
        }
    }
    return nullptr;
}

int LabAssignment::get_Grade()
{
    return grade;
}

void LabAssignment::set_Grade(int newGrade)
{
    grade = newGrade;
}

Lab * LabAssignment::get_Lab()
{
    return linkedLab;
}

void LabAssignment::set_Lab(Lab *lab)
{
    linkedLab = lab;
}

void LabAssignment::set_Id(int id)
{
    ID = id;
}

int LabAssignment::get_Id()
{
    return ID;
}



