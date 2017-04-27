#include "labassignment.h"

//Lab assignment object. Each lab assignment has  a student, grade, applied rubric items,
//lab, and id associated with it.
int LabAssignment::idCount = 0;

//Constructor that sets id and id count.
LabAssignment::LabAssignment()
{
    ID = idCount;
    std::cout << "LabAssignment: " << std::to_string(ID) << " being created" << std::endl;
    idCount += 1;
}

//Destructor
LabAssignment::~LabAssignment()
{

}

//Sets student.
void LabAssignment::set_Student(Student *kid)
{
    student = kid;
}

//Gets student.
Student * LabAssignment::get_Student()
{
    return student;
}

//Adds new rubric item to vector of applied items.
void LabAssignment::new_RI(RubricItem *RIptr)
{
    appliedItems.push_back(RIptr);
}

//Returns rubric item with given subject
RubricItem * LabAssignment::get_RI(string subject)
{
    //Iterates through vector and checks subject with parameter subject
    //Returns null if rubric item is not in vector
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


//Adds comment to specific rubric item.
void LabAssignment::add_Comment(Comment *com, RubricItem *item)
{
    //Iterates through vector of applied rubric items
    //looking for rubric item.
    //If rubric item is found, comment is added to it.
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

//Returns comment.
Comment * LabAssignment::get_Comment(RubricItem *item, int num)
{
    //Iterates through vector of rubric items and returns comment
    //at index 'num'.
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

//Gets grade for assignement.
int LabAssignment::get_Grade()
{
    return grade;
}

//Sets grade for assignement
void LabAssignment::set_Grade(int newGrade)
{
    grade = newGrade;
}

//Gets lab for assignment.
Lab * LabAssignment::get_Lab()
{
    return linkedLab;
}

//Sets lab for assignment.
void LabAssignment::set_Lab(Lab *lab)
{
    linkedLab = lab;
}

//Sets id for database.
void LabAssignment::set_Id(int id)
{
    ID = id;
}

//Gets id for database.
int LabAssignment::get_Id()
{
    return ID;
}

//Gets rubric item ids.
vector <int> LabAssignment::get_RubricItem_Ids(){

    vector<int> ids;

    for(int i=0; i<appliedItems.size(); i++){
        ids.push_back(appliedItems.at(i)->get_Id());
    }

    return ids;
}

//Returns vector of applied rubric items.
vector <RubricItem *> LabAssignment::get_rubricItems(){
    return appliedItems;
}

