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
    items.at(num);
}
