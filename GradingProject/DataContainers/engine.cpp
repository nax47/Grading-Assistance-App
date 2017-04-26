#include "engine.h"

Engine::Engine(){

    dbControl = new DBEngine(new DBTool("GradingToolDB"));

    //Initialize the sectionList with data stored in the database
    sectionList = dbControl->get_sections();

    //Initialize the other object vectors with data from the database
    students = dbControl->get_students();
    labs = dbControl->get_labs();
    templates = dbControl->get_templates();
    labAssignments = dbControl->get_labAssignments();
    rubricItems = dbControl->get_rubricItems();
    comments = dbControl->get_comments();

    std::cout << "restored items" << std::endl;

    //debugging
    for(int i=0; i<sectionList.size(); i++){
        std::cout << "Section: " << std::to_string(sectionList.at(i)->get_Id()) << std::endl;
    }

    //Update ID count for each class so subsequent objects are created with correct IDs
    Section::idCount = dbControl->get_max_section_id()+1;
    Student::idCount = dbControl->get_max_student_id()+1;
    Lab::idCount = dbControl->get_max_lab_id()+1;
    Template::idCount = dbControl->get_max_template_id()+1;
    LabAssignment::idCount = dbControl->get_max_labAssignment_id()+1;
    RubricItem::idCount = dbControl->get_max_rubricItem_id()+1;
    Comment::idCount = dbControl->get_max_comment_id()+1;
}

Engine::~Engine(){
    write_to_database();
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
    students.push_back(stu);
}

void Engine::add_Lab(int num)
{
    Lab * lab = new Lab(num);
    lab->set_Section(currSection);
    Template * labTemplate = new Template();
    lab->set_Template(labTemplate);
    currSection->add_Lab(lab);
    labs.push_back(lab);
    templates.push_back(labTemplate);
}

void Engine::new_LabAssignment()
{
    LabAssignment * LA = new LabAssignment();
    LA->set_Student(currStudent);
    LA->set_Lab(currLab);
    LA->set_Grade(100);
    currStudent->add_Lab(LA);
    labAssignments.push_back(LA);
}


void Engine::add_Rubric_Item(string subj, int point)
{
    RubricItem * rub = new RubricItem(subj, point);
    RubricItem * rub2 = new RubricItem(subj, point);
    currLabAssignment->new_RI(rub);
    currLab->get_Template()->add_RI(rub2);

    rubricItems.push_back(rub);
    rubricItems.push_back(rub2);

}

Comment * Engine::add_Comment(string comment, int lineNum, string fileName){
    Comment * com = new Comment(comment, lineNum, fileName);
    comments.push_back(com);
    return com;
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

//void Engine::add_Lab(int num)
//{
//    Lab * lab = new Lab(num);
//    lab->set_Section(currSection);
//    lab->set_Template(currTemplate);
//    currSection->add_Lab(lab);
//    labs.push_back(lab);
//}
LabAssignment * Engine::get_currLA()
{
    return currLabAssignment;
}

void Engine::start_Grading()
{
    LabAssignment * lab = new LabAssignment();

    currLab->set_Template(currLab->get_Template());
    lab->set_Lab(currLab);
    lab->set_Student(currStudent);
    lab->set_Grade(100);
    currStudent->add_Lab(lab);
    currLabAssignment = lab;
    labAssignments.push_back(lab);
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

void Engine::write_to_database(){

    for(int i=0; i<sectionList.size(); i++){
        Section * section = sectionList.at(i);
        dbControl->store_section(section->get_Id(), section->get_Student_Ids(), section->get_Lab_Ids());
    }

    for(int i=0; i<students.size(); i++){
        Student * student = students.at(i);
        dbControl->store_student(student->get_Id(), student->get_Name(), student->get_LabAssignment_Ids());
    }

    for(int i=0; i<labs.size(); i++){
        Lab * lab = labs.at(i);
        dbControl->store_lab(lab->get_Id(), lab->get_Section()->get_Id(), lab->get_labNum(), lab->get_Template()->get_Id());
    }

    for(int i=0; i<templates.size(); i++){
        Template * templ = templates.at(i);
        dbControl->store_template(templ->get_Id(), templ->get_RubricItem_Ids());
    }

    for(int i=0; i<labAssignments.size(); i++){
        LabAssignment * labAssignment = labAssignments.at(i);
        dbControl->store_labAssignment(labAssignment->get_Id(), labAssignment->get_Grade(), labAssignment->get_Student()->get_Id(), labAssignment->get_Lab()->get_Id(), labAssignment->get_RubricItem_Ids());
    }

    for(int i=0; i<rubricItems.size(); i++){
        RubricItem * rubricItem = rubricItems.at(i);
        dbControl->store_rubricItem(rubricItem->get_Id(), rubricItem->get_Subject(), rubricItem->get_Points(), rubricItem->get_Comment_Ids());
    }

    for(int i=0; i<comments.size(); i++){
        Comment * comment = comments.at(i);
        dbControl->store_comment(comment->get_Id(), comment->get_Comment(), comment->get_line(), comment->get_fileName(), comment->get_Rubric_Item()->get_Id());
    }
}


