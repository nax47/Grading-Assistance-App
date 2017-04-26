#include "template.h"

int Template::idCount = 0;

Template::Template()
{
    ID = idCount;
    idCount += 1;
}

Template::~Template()
{

}

void Template::add_RI(RubricItem *newRI)
{
    items.push_back(newRI);
}

RubricItem * Template::get_RI(int num)
{
    return items.at(num);

}

void Template::set_Id(int id)
{
    ID = id;
}

int Template::get_Id()
{
    return ID;
}

vector<RubricItem *> Template::getItems() {
    return items;
}

vector <int> Template::get_RubricItem_Ids(){

    vector<int> ids;

    for(int i=0; i<items.size(); i++){
        ids.push_back(items.at(i)->get_Id());
    }

    return ids;
}

vector <RubricItem *> Template::get_rubricItems(){
    return items;
}
