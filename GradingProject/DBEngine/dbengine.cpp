#include "dbengine.h"

DBEngine::DBEngine(){

}

DBEngine::DBEngine(DBTool * dbtool){
    this->dbtool = dbtool;
    initialize_main_tables();
    restore_data();
    sectionTable->drop();
    studentTable->drop();
    labTable->drop();
    templateTable->drop();
    labAssignmentTable->drop();
    rubricItemTable->drop();
    commentTable->drop();
    std::map<std::string, DBTable *>::iterator it = additionalTables.begin();
    while (it!=additionalTables.end()){
        it->second->drop();
        delete it->second;
        it++;
    }
}

DBEngine::~DBEngine(){
    delete sectionTable;
    delete studentTable;
    delete labTable;
    delete templateTable;
    delete labAssignmentTable;
    delete rubricItemTable;
    delete commentTable;

    std::map<std::string, DBTable *>::iterator it = additionalTables.begin();
    while (it!=additionalTables.end()){
        delete it->second;
        it++;
    }
}

void DBEngine::initialize_main_tables(){
    std::string sql_create;

    sql_create =  "CREATE TABLE ";
    sql_create += "sectionTable";
    sql_create += " ( ";
    sql_create += "  id INT PRIMARY KEY NOT NULL, ";
    sql_create += "  studentIdsTableName TEXT NOT NULL,";
    sql_create += "  labIdsTableName TEXT NOT NULL";
    sql_create += " );";

    sectionTable = new DBTable(dbtool, this, "sectionTable", sql_create);

    sql_create =  "CREATE TABLE ";
    sql_create += "studentTable";
    sql_create += " ( ";
    sql_create += "  id INT PRIMARY KEY NOT NULL, ";
    sql_create += "  name TEXT NOT NULL,";
    sql_create += "  labAssignmentIdsTableName TEXT NOT NULL";
    sql_create += " );";

    studentTable = new DBTable(dbtool, this, "studentTable", sql_create);

    sql_create =  "CREATE TABLE ";
    sql_create += "labTable";
    sql_create += " ( ";
    sql_create += "  id INT PRIMARY KEY NOT NULL, ";
    sql_create += "  sectionId INT  NOT NULL, ";
    sql_create += "  labNum INT  NOT NULL, ";
    sql_create += "  templateId INT  NOT NULL ";
    sql_create += " );";

    labTable = new DBTable(dbtool, this, "labTable", sql_create);

    sql_create =  "CREATE TABLE ";
    sql_create += "templateTable";
    sql_create += " ( ";
    sql_create += "  id INT PRIMARY KEY NOT NULL, ";
    sql_create += "  rubricItemIdsTableName TEXT NOT NULL";
    sql_create += " );";

    templateTable = new DBTable(dbtool, this, "templateTable", sql_create);

    sql_create =  "CREATE TABLE ";
    sql_create += "labAssignmentTable";
    sql_create += " ( ";
    sql_create += "  id INT PRIMARY KEY NOT NULL, ";
    sql_create += "  grade INT  NOT NULL, ";
    sql_create += "  studentId INT  NOT NULL, ";
    sql_create += "  labId INT  NOT NULL, ";
    sql_create += "  rubricItemIdsTableName TEXT NOT NULL";
    sql_create += " );";

    labAssignmentTable = new DBTable(dbtool, this, "labAssignmentTable", sql_create);

    sql_create =  "CREATE TABLE ";
    sql_create += "rubricItemTable";
    sql_create += " ( ";
    sql_create += "  id INT PRIMARY KEY NOT NULL, ";
    sql_create += "  subject TEXT NOT NULL,";
    sql_create += "  points INT  NOT NULL, ";
    sql_create += "  commentIdsTableName TEXT NOT NULL";
    sql_create += " );";

    rubricItemTable = new DBTable(dbtool, this, "rubricItemTable", sql_create);

    sql_create =  "CREATE TABLE ";
    sql_create += "commentTable";
    sql_create += " ( ";
    sql_create += "  id INT PRIMARY KEY NOT NULL, ";
    sql_create += "  comment TEXT NOT NULL,";
    sql_create += "  lineNum INT  NOT NULL, ";
    sql_create += "  filename TEXT NOT NULL,";
    sql_create += "  rubricItemId INT  NOT NULL ";
    sql_create += " );";

    commentTable = new DBTable(dbtool, this, "commentTable", sql_create);
}

void DBEngine::store_section(int id, std::vector<int> studentIds, std::vector<int> labIds){

    std::string studentIdsTableString = "section"+std::to_string(id)+"studentIdsTable";
    std::string labIdsTableString = "section"+std::to_string(id)+"labIdsTable";

    create_additional_table(studentIds, studentIdsTableString);
    create_additional_table(labIds, labIdsTableString);

    std::string sql_add_row;
    char  tempval[128];

    sql_add_row  = "INSERT INTO ";
    sql_add_row += "sectionTable";
    sql_add_row += " ( id, studentIdsTableName, labIdsTableName ) ";
    sql_add_row += "VALUES (";

    sprintf (tempval, "%d", id);
    sql_add_row += tempval;
    sql_add_row += ", ";

    sql_add_row += "\"";
    sql_add_row += studentIdsTableString;
    sql_add_row += "\", ";

    sql_add_row += "\"";
    sql_add_row += labIdsTableString;
    sql_add_row += "\"";

    sql_add_row += " );";

    sectionTable->add_row(sql_add_row);
}

void DBEngine::store_student(int id, std::string name, std::vector<int> labAssignmentIds){

    std::string labAssignmentIdsTableString = "student"+std::to_string(id)+"labAssignmentIdsTable";

    create_additional_table(labAssignmentIds, labAssignmentIdsTableString);

    std::string sql_add_row;
    char  tempval[128];

    sql_add_row  = "INSERT INTO ";
    sql_add_row += "studentTable";
    sql_add_row += " ( id, name, labAssignmentIdsTableName ) ";
    sql_add_row += "VALUES (";

    sprintf (tempval, "%d", id);
    sql_add_row += tempval;
    sql_add_row += ", ";

    sql_add_row += "\"";
    sql_add_row += name;
    sql_add_row += "\", ";

    sql_add_row += "\"";
    sql_add_row += labAssignmentIdsTableString;
    sql_add_row += "\"";

    sql_add_row += " );";

    studentTable->add_row(sql_add_row);
}

void DBEngine::store_lab(int id, int sectionId, int labNum, int templateId){

    std::string sql_add_row;
    char  tempval[128];

    sql_add_row  = "INSERT INTO ";
    sql_add_row += "labTable";
    sql_add_row += " ( id, sectionId, labNum, templateId ) ";
    sql_add_row += "VALUES (";

    sprintf (tempval, "%d", id);
    sql_add_row += tempval;
    sql_add_row += ", ";

    sprintf (tempval, "%d", sectionId);
    sql_add_row += tempval;
    sql_add_row += ", ";

    sprintf (tempval, "%d", labNum);
    sql_add_row += tempval;
    sql_add_row += ", ";

    sprintf (tempval, "%d", templateId);
    sql_add_row += tempval;;

    sql_add_row += " );";

    labTable->add_row(sql_add_row);

}

void DBEngine::store_template(int id, std::vector<int> rubricItemIds){

    std::string rubricItemIdsTableString = "template"+std::to_string(id)+"rubricItemIdsTable";

    create_additional_table(rubricItemIds, rubricItemIdsTableString);

    std::string sql_add_row;
    char  tempval[128];

    sql_add_row  = "INSERT INTO ";
    sql_add_row += "templateTable";
    sql_add_row += " ( id, rubricItemIdsTableName ) ";
    sql_add_row += "VALUES (";

    sprintf (tempval, "%d", id);
    sql_add_row += tempval;
    sql_add_row += ", ";

    sql_add_row += "\"";
    sql_add_row += rubricItemIdsTableString;
    sql_add_row += "\"";

    sql_add_row += " );";

    templateTable->add_row(sql_add_row);
}

void DBEngine::store_labAssignment(int id, int grade, int studentId, int labId, std::vector<int> rubricItemIds){

    std::string rubricItemIdsTableString = "labAssignment"+std::to_string(id)+"rubricItemIdsTable";

    create_additional_table(rubricItemIds, rubricItemIdsTableString);

    std::string sql_add_row;
    char  tempval[128];

    sql_add_row  = "INSERT INTO ";
    sql_add_row += "labAssignmentTable";
    sql_add_row += " ( id, grade, studentId, labId, rubricItemIdsTableName ) ";
    sql_add_row += "VALUES (";

    sprintf (tempval, "%d", id);
    sql_add_row += tempval;
    sql_add_row += ", ";

    sprintf (tempval, "%d", grade);
    sql_add_row += tempval;
    sql_add_row += ", ";

    sprintf (tempval, "%d", studentId);
    sql_add_row += tempval;
    sql_add_row += ", ";

    sprintf (tempval, "%d", labId);
    sql_add_row += tempval;;
    sql_add_row += ", ";

    sql_add_row += "\"";
    sql_add_row += rubricItemIdsTableString;
    sql_add_row += "\"";

    sql_add_row += " );";

    labAssignmentTable->add_row(sql_add_row);
}

void DBEngine::store_rubricItem(int id, std::string subject, int points, std::vector<int> commentIds){

    std::string commentIdsTableString = "rubricItem"+std::to_string(id)+"commentIdsTable";

    create_additional_table(commentIds, commentIdsTableString);

    std::string sql_add_row;
    char  tempval[128];

    sql_add_row  = "INSERT INTO ";
    sql_add_row += "rubricItemTable";
    sql_add_row += " ( id, subject, points, commentIdsTableName ) ";
    sql_add_row += "VALUES (";

    sprintf (tempval, "%d", id);
    sql_add_row += tempval;
    sql_add_row += ", ";

    sql_add_row += "\"";
    sql_add_row += subject;
    sql_add_row += "\", ";

    sprintf (tempval, "%d", points);
    sql_add_row += tempval;;
    sql_add_row += ", ";

    sql_add_row += "\"";
    sql_add_row += commentIdsTableString;
    sql_add_row += "\"";

    sql_add_row += " );";

    rubricItemTable->add_row(sql_add_row);
}

void DBEngine::store_comment(int id, std::string comment, int lineNum, std::string filename, int rubricItemId){

    std::string sql_add_row;
    char  tempval[128];

    sql_add_row  = "INSERT INTO ";
    sql_add_row += "commentTable";
    sql_add_row += " ( id, comment, lineNum, filename, rubricItemId ) ";
    sql_add_row += "VALUES (";

    sprintf (tempval, "%d", id);
    sql_add_row += tempval;
    sql_add_row += ", ";

    sql_add_row += "\"";
    sql_add_row += comment;
    sql_add_row += "\", ";

    sprintf (tempval, "%d", lineNum);
    sql_add_row += tempval;;
    sql_add_row += ", ";

    sql_add_row += "\"";
    sql_add_row += filename;
    sql_add_row += "\", ";

    sprintf (tempval, "%d", rubricItemId);
    sql_add_row += tempval;;

    sql_add_row += " );";

    commentTable->add_row(sql_add_row);
}

void DBEngine::create_additional_table(std::vector<int> ids, std::string tableName){

    std::string sql_create;

    sql_create =  "CREATE TABLE ";
    sql_create += tableName;
    sql_create += " ( ";
    sql_create += "  id INT PRIMARY KEY NOT NULL ";
    sql_create += " );";

    DBTable * table = new DBTable(dbtool, this, tableName, sql_create);

    std::string sql_add_row;
    char  tempval[128];

    for(int i=0; i<ids.size(); i++){

        sql_add_row  = "INSERT INTO ";
        sql_add_row += tableName;
        sql_add_row += " ( id ) ";
        sql_add_row += "VALUES (";

        sprintf (tempval, "%d", ids.at(i));
        sql_add_row += tempval;

        sql_add_row += " );";

        table->add_row(sql_add_row);
    }

    additionalTables[tableName] = table;
}

void DBEngine::restore_section_data(char **data){

    int id = std::stoi(std::string(data[0]));
    additionalTableNames.push_back(std::string(data[1]));
    additionalTableNames.push_back(std::string(data[2]));

    Section * section;

    if(sections.find(id) == sections.end())
        section = new Section();
    else
        section = sections[id];

    section->set_Id(id);

    sections[id] = section;
}

void DBEngine::restore_student_data(char **data){

    int id = std::stoi(std::string(data[0]));
    std::string name = std::string(data[1]);
    additionalTableNames.push_back(std::string(data[2]));

    Student * student;

    if(students.find(id) == students.end())
        student = new Student();
    else
        student = students[id];

    student->set_Id(id);
    student->set_Name(name);

    students[id] = student;
}

void DBEngine::restore_lab_data(char **data){

    int id = std::stoi(std::string(data[0]));
    int sectionId = std::stoi(std::string(data[1]));
    int labNum = std::stoi(std::string(data[2]));
    int templateId = std::stoi(std::string(data[3]));
    Lab * lab;
    Section * section;
    Template * templ;

    if(labs.find(id) == labs.end())
        lab = new Lab();
    else
        lab = labs[id];

    if(sections.find(sectionId) == sections.end()){
        section = new Section();
        sections[sectionId] = section;
    }
    else
        section = sections[sectionId];

    if(templates.find(templateId) == templates.end()){
        templ = new Template();
        templates[templateId] = templ;
    }
    else
        templ = templates[templateId];

    lab->set_Id(id);
    lab->set_labNum(labNum);
    lab->set_Section(section);
    lab->set_Template(templ);

    labs[id] = lab;
}

void DBEngine::restore_template_data(char **data){

    int id = std::stoi(std::string(data[0]));
    additionalTableNames.push_back(std::string(data[1]));

    Template * templ;

    if(templates.find(id) == templates.end())
        templ = new Template();
    else
        templ = templates[id];

    templ->set_Id(id);

    templates[id] = templ;
}

void DBEngine::restore_labAssignment_data(char **data){

    int id = std::stoi(std::string(data[0]));
    int grade = std::stoi(std::string(data[1]));
    int studentId = std::stoi(std::string(data[2]));
    int labId = std::stoi(std::string(data[3]));
    additionalTableNames.push_back(std::string(data[4]));

    LabAssignment * labAssignment;
    Student * student;
    Lab * lab;

    if(labAssignments.find(id) == labAssignments.end())
        labAssignment = new LabAssignment();
    else
        labAssignment = labAssignments[id];

    if(students.find(studentId) == students.end()){
        student = new Student();
        students[studentId] = student;
    }
    else
        student = students[studentId];

    if(labs.find(labId) == labs.end()){
        lab = new Lab();
        labs[labId] = lab;
    }
    else
        lab = labs[labId];

    labAssignment->set_Id(id);
    labAssignment->set_Grade(grade);
    labAssignment->set_Student(student);
    labAssignment->set_Lab(lab);

    labAssignments[id] = labAssignment;
}

void DBEngine::restore_rubricItem_data(char **data){

    int id = std::stoi(std::string(data[0]));
    std::string subject = std::string(data[1]);
    int points = std::stoi(std::string(data[2]));
    additionalTableNames.push_back(std::string(data[3]));

    RubricItem * rubricItem;

    if(rubricItems.find(id) == rubricItems.end())
        rubricItem = new RubricItem();
    else
        rubricItem = rubricItems[id];

    rubricItem->set_Id(id);
    rubricItem->set_Subject(subject);
    rubricItem->set_Points(points);

    rubricItems[id] = rubricItem;

}

void DBEngine::restore_comment_data(char **data){
    int id = std::stoi(std::string(data[0]));
    std::string commentString = std::string(data[1]);
    int lineNum = std::stoi(std::string(data[2]));
    std::string fileName = std::string(data[3]);
    int rubricItemId = std::stoi(std::string(data[4]));
    Comment * comment;
    RubricItem * rubricItem;

    if(comments.find(id) == comments.end())
        comment = new Comment();
    else
        comment = comments[id];

    if(rubricItems.find(rubricItemId) == rubricItems.end()){
        rubricItem = new RubricItem();
        rubricItems[rubricItemId] = rubricItem;
    }
    else
        rubricItem = rubricItems[rubricItemId];

    comment->set_Id(id);
    comment->change_Comment(commentString);
    comment->set_line(lineNum);
    comment->set_fileName(fileName);
    comment->set_Rubric_Item(rubricItem);

    comments[id] = comment;
}

void DBEngine::restore_additional_table_data(string tableName, char **data){

    if(tableName.substr(0,6) == "section"){
        int id = stoi(tableName.substr(7,7));

        if(tableName.substr(8,14) == "student"){
            int studentId = std::stoi(std::string(data[0]));
            sections[id]->add_Student(students[studentId]);
        }
        else if(tableName.substr(8,10) == "lab"){
            int labId = std::stoi(std::string(data[0]));
            sections[id]->add_Lab(labs[labId]);
        }
    }

    else if(tableName.substr(0,6) == "student"){
        int id = stoi(tableName.substr(7,7));
        int labAssignmentId = std::stoi(std::string(data[0]));
        students[id]->add_Lab(labAssignments[labAssignmentId]);
    }

    else if(tableName.substr(0,7) == "template"){
        int id = stoi(tableName.substr(8,8));
        int rubricItemId = std::stoi(std::string(data[0]));
        templates[id]->add_RI(rubricItems[rubricItemId]);
    }

    else if(tableName.substr(0,12) == "labAssignment"){
        int id = stoi(tableName.substr(13,13));
        int rubricItemId = std::stoi(std::string(data[0]));
        labAssignments[id]->new_RI(rubricItems[rubricItemId]);
    }

    else if(tableName.substr(0,9) == "rubricItem"){
        int id = stoi(tableName.substr(13,13));
        int commentId = std::stoi(std::string(data[0]));
        rubricItems[id]->add_Comment(comments[commentId]);
    }

}

void DBEngine::restore_data(){

    sectionTable->select_all();
    studentTable->select_all();
    labTable->select_all();
    templateTable->select_all();
    labAssignmentTable->select_all();
    rubricItemTable->select_all();
    commentTable->select_all();

    std::string sql_create;
    std::string tableName;

    sql_create =  "CREATE TABLE ";
    sql_create += tableName;
    sql_create += " ( ";
    sql_create += "  id INT PRIMARY KEY NOT NULL ";
    sql_create += " );";

    for(int i=0; i<additionalTableNames.size(); i++){
        tableName = additionalTableNames.at(i);

        sql_create =  "CREATE TABLE ";
        sql_create += tableName;
        sql_create += " ( ";
        sql_create += "  id INT PRIMARY KEY NOT NULL ";
        sql_create += " );";

        additionalTables[tableName] = new DBTable(dbtool, this, tableName, sql_create);
    }

    std::map<std::string, DBTable *>::iterator it = additionalTables.begin();
    while (it!=additionalTables.end()){
        it->second->select_all();
        it++;
    }
}

std::vector<Section *> DBEngine::get_stored_data(){

    std::vector<Section *> restoredSections;

    std::map<int, Section *>::iterator it = sections.begin();
    while (it!=sections.end()){
        restoredSections.push_back(it->second);
        it++;
    }

    return restoredSections;
}
