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

    void set_Section(Section * sec);
    Section * get_Section();

    void set_Template(Template * tem);
    Template * get_Template();

private:

    Template * tmplate;
    Section * section;


};

#endif // LAB_H
