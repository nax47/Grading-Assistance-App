#ifndef TEMPLATE_H
#define TEMPLATE_H

#include <iostream>
#include <string>
#include <vector>
#include "rubricitem.h"
#include "comment.h"
#include "section.h"

using namespace std;

class Template
{
public:
    Template();
    ~Template();


    void add_RI(RubricItem * newRI);
    RubricItem * get_RI(int num);

private:
    vector <RubricItem *> items;
};

#endif // TEMPLATE_H
