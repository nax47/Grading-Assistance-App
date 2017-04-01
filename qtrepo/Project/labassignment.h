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

class LabAssignment
{
public:
    LabAssignment();
    ~LabAssignment();

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

private:

    Student * student;
    vector <RubricItem *> appliedItems;
    int grade;
    Lab * linkedLab;
};

#endif // LABASSIGNMENT_H
