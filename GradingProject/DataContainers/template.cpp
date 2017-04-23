#include "template.h"

Template::Template()
{

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
