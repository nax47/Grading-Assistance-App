#include "dbengine.h"

DBEngine::DBEngine(){

}

DBEngine::DBEngine(DBTool * dbtool){
    this->dbtool = dbtool;
    initialize_main_tables();
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

    sectionTable = new DBTable(dbtool, "sectionTable", sql_create);

    sql_create =  "CREATE TABLE ";
    sql_create += "studentTable";
    sql_create += " ( ";
    sql_create += "  id INT PRIMARY KEY NOT NULL, ";
    sql_create += "  name TEXT NOT NULL,";
    sql_create += "  labAssignmentIdsTableName TEXT NOT NULL";
    sql_create += " );";

    studentTable = new DBTable(dbtool, "studentTable", sql_create);

    sql_create =  "CREATE TABLE ";
    sql_create += "labTable";
    sql_create += " ( ";
    sql_create += "  id INT PRIMARY KEY NOT NULL, ";
    sql_create += "  sectionId INT  NOT NULL, ";
    sql_create += "  labNum INT  NOT NULL, ";
    sql_create += "  templateId INT  NOT NULL ";
    sql_create += " );";

    labTable = new DBTable(dbtool, "labTable", sql_create);

    sql_create =  "CREATE TABLE ";
    sql_create += "templateTable";
    sql_create += " ( ";
    sql_create += "  id INT PRIMARY KEY NOT NULL, ";
    sql_create += "  rubricItemIdsTableName TEXT NOT NULL";
    sql_create += " );";

    templateTable = new DBTable(dbtool, "templateTable", sql_create);

    sql_create =  "CREATE TABLE ";
    sql_create += "labAssignmentTable";
    sql_create += " ( ";
    sql_create += "  id INT PRIMARY KEY NOT NULL, ";
    sql_create += "  grade INT  NOT NULL, ";
    sql_create += "  studentId INT  NOT NULL, ";
    sql_create += "  labId INT  NOT NULL, ";
    sql_create += "  rubricItemIdsTableName TEXT NOT NULL";
    sql_create += " );";

    labAssignmentTable = new DBTable(dbtool, "labAssignmentTable", sql_create);

    sql_create =  "CREATE TABLE ";
    sql_create += "rubricItemTable";
    sql_create += " ( ";
    sql_create += "  id INT PRIMARY KEY NOT NULL, ";
    sql_create += "  subject TEXT NOT NULL,";
    sql_create += "  points INT  NOT NULL, ";
    sql_create += "  commentIdsTableName TEXT NOT NULL";
    sql_create += " );";

    rubricItemTable = new DBTable(dbtool, "rubricItemTable", sql_create);

    sql_create =  "CREATE TABLE ";
    sql_create += "commentTable";
    sql_create += " ( ";
    sql_create += "  id INT PRIMARY KEY NOT NULL, ";
    sql_create += "  comment TEXT NOT NULL,";
    sql_create += "  lineNum INT  NOT NULL, ";
    sql_create += "  filename TEXT NOT NULL,";
    sql_create += "  rubricItemId INT  NOT NULL ";
    sql_create += " );";

    commentTable = new DBTable(dbtool, "commentTable", sql_create);
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

    DBTable * table = new DBTable(dbtool, tableName, sql_create);

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
