#include "lab.h"

Lab::Lab()
{

}

Lab::~Lab()
{

}

Lab::Lab(int num)
{
    labNum = num;
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

void Lab::set_labNum(int num)
{
    labNum = num;
}

int Lab::get_labNum()
{
    return labNum;
}
