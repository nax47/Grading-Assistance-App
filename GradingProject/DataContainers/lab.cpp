#include "lab.h"

Lab::Lab()
{

}

Lab::~Lab()
{

}

void Lab::set_Section(Section *sec)
{
    section = sec;
}

Section * Lab::get_Section()
{
    return section;
}

void Lab::set_Template(Template *tem)
{
    tmplate = tem;
}

Template * Lab::get_Template()
{
    return tmplate;
}
