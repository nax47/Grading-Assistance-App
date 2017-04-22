#ifndef DBENGINE_H
#define DBENGINE_H

#include "dbtable.h"
#include "dbtool.h"

class DBTool;

class DBEngine{
public:
    DBEngine(DBTool * dbtool);
    ~DBEngine();
    void store_section(int id);
    void store_student(int id, std::string name);
    void store_lab(int id, int sectionId, int labNum, int templateId);
    void store_template(int id);
    void store_labAssignment(int id, int grade, int studentId, int labId);
    void store_rubricItem(int id, std::string subjects, int points);
    void store_comment(int id, std::string comment, int lineNum, std::string filename, int rubricItemId);

private:
    DBTool * dbtool;
};

#endif // DBENGINE_H
