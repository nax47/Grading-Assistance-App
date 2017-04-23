#ifndef LAB_H
#define LAB_H

#include <iostream>
#include <string>
#include <vector>
#include "rubricitem.h"
#include "template.h"
#include "comment.h"
#include "section.h"

using namespace std;

class Template;
class Section;


class Lab
{
public:
    Lab();
    ~Lab();
    Lab(int num);

    void set_Section(Section * sec);
    Section * get_Section();

    void set_Template(Template * tem);
    Template * get_Template();

    void set_labNum(int num);
    int get_labNum();

    void set_Id(int id);
    int get_Id();

private:

    Template * tmplate;
    int labNum;
    Section * section;
    int ID;

};

#endif // LAB_H
