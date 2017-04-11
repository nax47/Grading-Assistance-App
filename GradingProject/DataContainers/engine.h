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

class Engine
{
public:
    Engine();
    ~Engine();

    void add_Section(Section * sec);
    Section * get_Section(int id);

private:

    vector <Section *> sectionList;
    DBEngine * dbControl;
};

#endif // ENGINE_H
