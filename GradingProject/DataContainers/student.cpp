#include "student.h"

//Student object.
//Each student has a name, a vector of graded labs, and
//an id associated with it.
int Student::idCount = 0;


//Constructor that sets id and id count.
Student::Student()
{
    ID = idCount;
    std::cout << "Student: " << std::to_string(ID) << " being created" << std::endl;
    idCount += 1;
}

//Constructor that sets student name, id, and id count.
Student::Student(string name)
{
    studentName = name;
    ID = idCount;
     std::cout << "Student: " << std::to_string(ID) << " being created" << std::endl;
    idCount += 1;
}

//Destructor.
Student::~Student()
{

}

//Sets name of student.
void Student::set_Name(string name)
{
    studentName = name;
}

//Gets name of student.
string Student::get_Name()
{
    return studentName;
}

//Adds lab to list of student's lab.
void Student::add_Lab(LabAssignment *newLab)
{
    gradedLabs.push_back(newLab);
}

//Gets lab at given index.
LabAssignment * Student::get_Lab(int labNum)
{
    return gradedLabs.at(labNum);
}

//Sets id for database.
void Student::set_Id(int id)
{
    ID = id;
}

//Gets id for database.
int Student::get_Id()
{
    return ID;
}

//Returns vector of lab assignment ids.
vector <int> Student::get_LabAssignment_Ids(){
    //Iterates through list of graded labs,
    //and adds id of labs to vector.
    vector<int> ids;
    for(int i=0; i<gradedLabs.size(); i++){
        ids.push_back(gradedLabs.at(i)->get_Id());
    }
    return ids;
}

//Returns vector of graded labs.
vector <LabAssignment *> Student::get_labAssignments(){
    return gradedLabs;
}
