#include "section.h"

//Section Object
//Each section has a list of students, a list of labs,
//and an id associated with it.

int Section::idCount = 0;

//Constructor that sets id and id count.
Section::Section()
{
    ID = idCount;
    idCount += 1;
}

//Destructor
Section::~Section()
{

}

//Adds Student to list of students.
void Section::add_Student(Student *stu)
{
    studentList.push_back(stu);
}

//Returns the amount of students stored in list.
int Section::get_Student_Size()
{
    return studentList.size();
}

//Gets name of student at given index
//in student list.
string Section::get_Student_Name(int num)
{
    Student * tmp;
    tmp = studentList.at(num);
    return tmp->get_Name();
}

//Returns student by name.
Student * Section::get_Student(string name)
{
    //Iterates through list of students
    //and compares name of current
    //student to parameter name
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

//Sets id for database.
void Section::set_Id(int id)
{
    ID = id;
}

//Gets id for database.
int Section::get_Id()
{
    return ID;
}

//Adds new lab to section.
void Section::add_Lab(Lab *newLab)
{
    labList.push_back(newLab);
}

//Returns number of labs in section.
int Section::get_Lab_Size()
{
    return labList.size();
}

//Returns lab at given index in
//list of labs.
Lab * Section::get_Lab(int num)
{
    return labList.at(num);
}

//Returns vector of student ids.
vector <int> Section::get_Student_Ids(){
    //Iterates through list of students and adds id
    //of each student to vector of ids.
    vector<int> ids;
    for(int i=0; i<studentList.size(); i++){
        ids.push_back(studentList.at(i)->get_Id());
    }
    return ids;
}

//Returns vector of lab ids.
vector <int> Section::get_Lab_Ids(){
    //Iterates through list of labs and adds id
    //of each lab to vector of ids.
    vector<int> ids;
    for(int i=0; i<labList.size(); i++){
        ids.push_back(labList.at(i)->get_Id());
    }
    return ids;
}

//Returns list of students.
vector <Student *> Section::get_students(){
    return studentList;
}

//Returns list of labs.
vector <Lab *> Section::get_labs(){
    return labList;
}

