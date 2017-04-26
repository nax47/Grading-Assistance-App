#ifndef LABASSIGNMENT_H
#define LABASSIGNMENT_H

#include <iostream>
#include <string>
#include <vector>
#include "rubricitem.h"
#include "student.h"
#include "comment.h"
#include "lab.h"

using namespace std;

class Student;
class Lab;

class LabAssignment
{
public:
    LabAssignment();
    ~LabAssignment();

    //Setters, getters, and metehods for adding data.
    void set_Student(Student * kid);
    Student * get_Student();

    void new_RI(RubricItem * RIptr);
    RubricItem * get_RI(string subject);

    void add_Comment(Comment * com, RubricItem * item);
    Comment * get_Comment(RubricItem * item, int num);

    int get_Grade();
    void set_Grade(int newGrade);

    Lab * get_Lab();
    void set_Lab(Lab * lab);

    void set_Id(int id);
    int get_Id();

    vector <int> get_RubricItem_Ids();

    vector <RubricItem *> get_rubricItems();

    static int idCount;

private:

    Student * student; //Student
    vector <RubricItem *> appliedItems; //applied rubric items
    int grade; //grade of assignment
    Lab * linkedLab; //Lab that assignement is linked to
    int ID; //id for database
};


#endif // LABASSIGNMENT_H
