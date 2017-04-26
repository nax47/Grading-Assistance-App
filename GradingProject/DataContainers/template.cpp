#include "template.h"

//Template object.
//Each template has a vector of rubric items and an id
//associated with it.

int Template::idCount = 0;

//Constructor that sets id and id count.
Template::Template()
{
    ID = idCount;
    idCount += 1;
}

//Destructor.
Template::~Template()
{

}

//Adds rubric item to vector of rubric items.
void Template::add_RI(RubricItem *newRI)
{
    items.push_back(newRI);
}

//Returns rubric item in vector
//at given index.
RubricItem * Template::get_RI(int num)
{
    return items.at(num);
}

//Sets id for database.
void Template::set_Id(int id)
{
    ID = id;
}

//Gets id for database.
int Template::get_Id()
{
    return ID;
}

//Returns entire vector of rubric items.
vector<RubricItem *> Template::getItems() {
    return items;
}

//Returns vector of rubric item ids for database.
vector <int> Template::get_RubricItem_Ids(){
    //Iterates through list of rubric items,
    //and adds ids to vector.
    vector<int> ids;
    for(int i=0; i<items.size(); i++){
        ids.push_back(items.at(i)->get_Id());
    }
    return ids;
}

//Returns entire vector of rubric items.
vector <RubricItem *> Template::get_rubricItems(){
    return items;
}
