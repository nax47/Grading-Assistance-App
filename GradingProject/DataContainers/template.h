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

    void set_Id(int id);
    int get_Id();
    vector<RubricItem*> getItems();

    vector <int> get_RubricItem_Ids();

    vector <RubricItem *> get_rubricItems();

    static int idCount;

private:
    vector <RubricItem *> items;
    int ID;
};


#endif // TEMPLATE_H
