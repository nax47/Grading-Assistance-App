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
    Comment * add_Comment(std::string comment, int lineNum, std::string fileName);

    void start_Grading();
    //GUI set up methods
    vector <int> section_Drop_SetUp();
    vector <int> labNum_Drop_SetUp();
    vector <string> student_Drop_SetUp();



    void add_Rubric_Item(string subj, int point);


private:

    void write_to_database();

    Section * currSection = nullptr;
    Lab * currLab = nullptr;
    Student * currStudent = nullptr;
    LabAssignment * currLabAssignment = nullptr;
    Template * currTemplate = nullptr;


    vector <Section *> sectionList;

    vector <Student *> students;

    vector <Lab *> labs;

    vector <Template *> templates;

    vector <LabAssignment *> labAssignments;

    vector <RubricItem *> rubricItems;

    vector <Comment *> comments;

    DBEngine * dbControl;
};

#endif // ENGINE_H
