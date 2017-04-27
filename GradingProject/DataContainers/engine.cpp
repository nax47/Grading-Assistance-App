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
    cout << sectionList.size() << endl;
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
    delete dbControl;
}

/**
 * @brief Engine::add_Section creates new section with inputed id
 * @param id
 */
void Engine::add_Section(int id)
{
    //creates new section with inputed id
    Section * sec = new Section();
    sec->set_Id(id);
    sectionList.push_back(sec);
}

/**
 * @brief Engine::get_Section
 * @param id
 * @return found Section pointer
 */
Section * Engine::get_Section(int id)
{
    Section * tmpPtr;
    //loops through the sections and returns the section that matches id
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

vector<Section*> Engine::get_sections() {
    return sectionList;
}

/**
 * @brief Engine::get_Lab
 * @param num
 * @return found Lab pointer
 */
Lab * Engine::get_Lab(int num)
{
    Lab * tmpPtr;
    //searches through all labs in current section and finds the one that matchis input num
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

/**
 * @brief Engine::add_Student creates a new student with name input and adds them to the current student
 * @param name
 */
void Engine::add_Student(string name)
{
    Student * stu = new Student(name);
    currSection->add_Student(stu);
    students.push_back(stu);
}

/**
 * @brief Engine::add_Lab creates a new lab and template for the current section
 * @param num
 */
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

/**
 * @brief Engine::new_LabAssignment creates a new lab assignment for the current student
 */
void Engine::new_LabAssignment()
{
    LabAssignment * LA = new LabAssignment();
    LA->set_Student(currStudent);
    LA->set_Lab(currLab);
    LA->set_Grade(100);
    currStudent->add_Lab(LA);
    labAssignments.push_back(LA);
}

/**
 * @brief Engine::add_Rubric_Item creates a new rubric item to be added to current lab assignment and lab template
 * @param subj rubric item subject
 * @param point deducted
 * @param max points
 */
void Engine::add_Rubric_Item(string subj, int point, int max)
{
    RubricItem * rub = new RubricItem(subj, point);
    RubricItem * rub2 = new RubricItem(subj, point);
    rub->set_maxP(max);
    rub2->set_maxP(max);
    currLabAssignment->new_RI(rub);
    currLab->get_Template()->add_RI(rub2);

    rubricItems.push_back(rub);
    rubricItems.push_back(rub2);

}

/**
 * @brief Engine::add_Comment generates a new comment
 * @param comment text input
 * @param lineNum where the comment was applied
 * @param fileName what file it was applied to
 * @return the generated comment pointer
 */
Comment * Engine::add_Comment(string comment, int lineNum, string fileName){
    Comment * com = new Comment(comment, lineNum, fileName);
    comments.push_back(com);
    return com;
}

/**
 * @brief Engine::set_currLab sets the current lab to the lab that matches id
 * @param id
 */
void Engine::set_currLab(int id)
{
    currLab = get_Lab(id);
}

/**
 * @brief Engine::set_currSection sets the current section to the section that matches id
 * @param id
 */
void Engine::set_currSection(int id)
{
    currSection = get_Section(id);
}

/**
 * @brief Engine::set_currStudent sets the current student to the student that matches name
 * @param name
 */
void Engine::set_currStudent(string name)
{
    currStudent = currSection->get_Student(name);
}

/**
 * @brief Engine::get_currStu
 * @return pointer to the current student
 */
Student * Engine::get_currStu()
{
    return currStudent;
}

/**
 * @brief Engine::get_currSec
 * @return pointer to the current section
 */
Section * Engine::get_currSec()
{
    return currSection;
}

/**
 * @brief Engine::get_currL
 * @return pointer to the current lab
 */
Lab * Engine::get_currL()
{
    return currLab;
}

/**
 * @brief Engine::get_currLA
 * @return pointer to the current lab assignment
 */
LabAssignment * Engine::get_currLA()
{
    return currLabAssignment;
}

/**
 * @brief Engine::start_Grading sets the data containers up using current items from gui.
 * @param loadLast from load last rubric button. sets up data containers with rubric items from previous template if true
 */
void Engine::start_Grading(bool loadLast)
{
    LabAssignment * lab = new LabAssignment();

    //currLab->set_Template(currLab->get_Template());
    lab->set_Lab(currLab);
    lab->set_Student(currStudent);
    lab->set_Grade(100);
    if(loadLast)
    {
        vector <RubricItem *> last = currLab->get_Template()->getItems();
        //gets all rubric items from previously made template and adds them to the new lab assignment
        for(int i = 0; i < last.size(); i++)
        {
            RubricItem * tp = last.at(i);
            RubricItem * temp = new RubricItem(tp->get_Subject(), tp->get_Points());
            temp->set_maxP(tp->get_maxP());

            lab->new_RI(temp);
        }
    }
    currStudent->add_Lab(lab);
    currLabAssignment = lab;
    labAssignments.push_back(lab);
}

/**
 * @brief Engine::section_Drop_SetUp creates a vector of all the section ids
 * @return created vector <int>
 */
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

/**
 * @brief Engine::labNum_Drop_SetUp creates a vector of all lab ids
 * @return created vector <int>
 */
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

/**
 * @brief Engine::student_Drop_SetUp creates a vector of all student names
 * @return created vector <string>
 */
vector <string> Engine::student_Drop_SetUp()
{
    vector <string> out;
    for(int i = 0; i < currSection->get_Student_Size(); i++)
    {
        out.push_back(currSection->get_Student_Name(i));
    }
    return out;
}

/**
 * @brief Engine::write_to_database
 */
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


