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

Lab * Engine::get_Lab(int num)
{
    Lab * tmpPtr;
    for(int i = 0; i < currSection->get_Lab_Size(); i++)
    {
        tmpPtr = currSection->get_Lab(i);
        if(tmpPtr->get_labNum() == num)
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

void Engine::add_Lab(int num)
{
    Lab * lab = new Lab(num);
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

void Engine::add_Rubric_Item(string subj, int point, string comm)
{
    RubricItem * rub = new RubricItem(subj, point);
    Comment * com = new Comment(comm);
    rub->add_Comment(com);
    currLabAssignment->new_RI(rub);
    currLab->get_Template()->add_RI(rub);

}


void Engine::set_currLab(int id)
{
    currLab = get_Lab(id);
}

void Engine::set_currSection(int id)
{
    currSection = get_Section(id);
}


void Engine::set_currStudent(string name)
{
    currStudent = currSection->get_Student(name);
}

Student * Engine::get_currStu()
{
    return currStudent;
}

Section * Engine::get_currSec()
{
    return currSection;
}

Lab * Engine::get_currL()
{
    return currLab;
}

LabAssignment * Engine::get_currLA()
{
    return currLabAssignment;
}

void Engine::start_Grading()
{
    LabAssignment * lab = new LabAssignment();
    Template * labTemplate = new Template();
    currLab->set_Template(labTemplate);
    lab->set_Lab(currLab);
    lab->set_Student(currStudent);
    lab->set_Grade(100);
    currStudent->add_Lab(lab);
    currLabAssignment = lab;
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
        int t = currSection->get_Lab(i)->get_labNum();
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
