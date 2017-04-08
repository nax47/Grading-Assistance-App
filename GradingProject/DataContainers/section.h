#ifndef SECTION_H
#define SECTION_H

#include <iostream>
#include <string>
#include <vector>
#include "rubricitem.h"
#include "template.h"
#include "student.h"
#include "lab.h"
#include "comment.h"

using namespace std;

class Student;
class Lab;

class Section
{
public:
    Section();
    ~Section();

    void add_Student(Student * stu);
    Student * get_Student(string name);

    void set_Id(int id);
    int get_Id();

    void add_Lab(Lab * newLab);
    Lab * get_Lab(int num);


private:

    vector <Student *> studentList;
    vector <Lab *> labList;
    int ID;
};

#endif // SECTION_H
