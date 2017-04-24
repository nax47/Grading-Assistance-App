#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <string>
#include <vector>
#include "rubricitem.h"
#include "template.h"
#include "student.h"
#include "lab.h"
#include "comment.h"
#include "section.h"
#include "../DBEngine/dbengine.h"
#include "../DBEngine/dbtable.h"
#include "../DBEngine/dbtool.h"


using namespace std;

class Section;
class DBEngine;
class Lab;
class Student;
class Template;
class RubricItem;
class LabAssignment;
class Comment;

class Engine
{
public:
    Engine();
    ~Engine();

    void add_Section(int id);
    Section * get_Section(int id);
    Lab * get_Lab(int num);


    //set currents will be used when section lab and student are picked in gui
    void set_currSection(int id);
    void set_currLab(int id);
    void set_currStudent(string name);

    //get currents
    Student * get_currStu();
    Lab * get_currL();
    Section * get_currSec();
    LabAssignment * get_currLA();

    // basic adds
    void add_Student(string name);
    void add_Lab(int num);
    void new_LabAssignment();

    void start_Grading();
    //GUI set up methods
    vector <int> section_Drop_SetUp();
    vector <int> labNum_Drop_SetUp();
    vector <string> student_Drop_SetUp();



    void add_Rubric_Item(string subj, int point, string comm);


private:

    Section * currSection = nullptr;
    Lab * currLab = nullptr;
    Student * currStudent = nullptr;
    LabAssignment * currLabAssignment = nullptr;
    Template * currTemplate = nullptr;


    vector <Section *> sectionList;

    DBEngine * dbControl;
};

#endif // ENGINE_H
