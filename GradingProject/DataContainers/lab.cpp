#include "lab.h"

//Lab Object. Each lab has a template, section, lab number, and id associated with it.

int Lab::idCount = 0;

//Default contructor that sets id and id count
Lab::Lab()
{
    ID = idCount;
    std::cout << "Lab: " << std::to_string(ID) << " being created" << std::endl;
    idCount += 1;
}

//Destructor
Lab::~Lab()
{

}

//Constructor that sets lab number, id, and id count
Lab::Lab(int num)
{
    labNum = num;
    ID = idCount;
    std::cout << "Lab: " << std::to_string(ID) << " being created" << std::endl;
    idCount += 1;
}

//Sets section.
void Lab::set_Section(Section *sec)
{
    section = sec;
}

//Gets section.
Section * Lab::get_Section()
{
    return section;
}

//Sets template.
void Lab::set_Template(Template *tem)
{
    tmplate = tem;
}

//Gets template.
Template * Lab::get_Template()
{
    return tmplate;
}


//Sets lab number.
void Lab::set_labNum(int num)
{
    labNum = num;
}

//Gets lab number.
int Lab::get_labNum()
{
    return labNum;
}

//Sets id for database.
void Lab::set_Id(int id)
{
    ID = id;
}

//Gets id for database.
int Lab::get_Id()
{
    return ID;
}
