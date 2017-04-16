#include "engine.h"

Engine::Engine(){
    dbControl = new DBEngine(new DBTool("GradingToolDB"));
}

Engine::~Engine(){

}

void Engine::add_Section(int id)
{
    Section * sec = new Section();
    sec->set_Id(id);
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

void Engine::add_Student(string name)
{
    Student * stu = new Student(name);
    currSection->add_Student(stu);
}

void Engine::add_Lab()
{
    Lab * lab = new Lab();
    lab->set_Section(currSection);
    lab->set_Template(currTemplate);
    currSection->add_Lab(lab);
}

void Engine::new_LabAssignment()
{
    LabAssignment * LA = new LabAssignment();
    LA->set_Student(currStudent);
    LA->set_Lab(currLab);
    LA->set_Grade(100);
    currStudent->add_Lab(LA);
}


void Engine::set_currLab(int id)
{
    currLab = currSection->get_Lab(id);
}

void Engine::set_currSection(int id)
{
    currSection = get_Section(id);
}


void Engine::set_currStudent(string name)
{
    currStudent = currSection->get_Student(name);
}



vector <int> Engine::section_Drop_SetUp()
{
    vector <int> out;

    for(int i = 0; i < sectionList.size(); i++)
    {
        Section * sectmp = sectionList.at(i);
        int tmp = sectmp->get_Id();
        out.push_back(tmp);
    }
    return out;
}

vector <int> Engine::labNum_Drop_SetUp()
{
    vector <int> out;
    int labSize = currSection->get_Lab_Size();

    for(int i = 0; i < labSize; i++)
    {
        int t = i + 1;
        out.push_back(t);
    }

    return out;
}

vector <string> Engine::student_Drop_SetUp()
{
    vector <string> out;
    for(int i = 0; i < currSection->get_Student_Size(); i++)
    {
        out.push_back(currSection->get_Student_Name(i));
    }
    return out;
}
