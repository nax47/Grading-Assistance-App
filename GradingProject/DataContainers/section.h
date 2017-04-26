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

    //Getters, setters, and add labs.
    void add_Student(Student * stu);
    int get_Student_Size();
    string get_Student_Name(int num);
    Student * get_Student(string name);

    void set_Id(int id);
    int get_Id();

    void add_Lab(Lab * newLab);
    int get_Lab_Size();
    Lab * get_Lab(int num);

    vector <int> get_Student_Ids();

    vector <int> get_Lab_Ids();

    vector <Student *> get_students();

    vector <Lab *> get_labs();

    static int idCount;

private:

    vector <Student *> studentList;
    vector <Lab *> labList;
    int ID;
};


#endif // SECTION_H
