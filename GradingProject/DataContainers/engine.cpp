#include "engine.h"

Engine::Engine(){
    dbControl = new DBEngine(new DBTool("GradingToolDB"));
}

Engine::~Engine(){

}

void Engine::add_Section(Section *sec)
{
    sectionList.push_back(sec);
}

Section * Engine::get_Section(int id)
{
    Section * tmpPtr;
    for(int i =0; i < sectionList.size(); i++)
    {
        tmpPtr = sectionList.at(i);
        if(tmpPtr->get_Id() == id)
        {
            return tmpPtr;
        }
    }
    return nullptr;
}
