#include "lab.h"

int Lab::idCount = 0;

Lab::Lab()
{
    ID = idCount;
    idCount += 1;
}

Lab::~Lab()
{

}

Lab::Lab(int num)
{
    labNum = num;
    ID = idCount;
    idCount += 1;
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

void Lab::set_Id(int id)
{
    ID = id;
}

int Lab::get_Id()
{
    return ID;
}
