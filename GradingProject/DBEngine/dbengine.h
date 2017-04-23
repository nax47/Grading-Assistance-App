#ifndef DBENGINE_H
#define DBENGINE_H

#include "dbtable.h"
#include "dbtool.h"
#include <vector>
#include <map>

class DBTool;

class DBEngine{
public:
    // Default constructor
    DBEngine();

    // Modified constructor takes in reference to the database tool
    DBEngine(DBTool * dbtool);

    // Destructor
    ~DBEngine();

    // Method to store a new row in the section table
    void store_section(int id, std::vector<int> studentIds, std::vector<int> labIds);

    // Method to store a new row in the student table
    void store_student(int id, std::string name, std::vector<int> labAssignmentIds);

    // Method to store a new row in the lab table
    void store_lab(int id, int sectionId, int labNum, int templateId);

    // Method to store a new row in the template table
    void store_template(int id, std::vector<int> rubricItemIds);

    // Method to store a new row in the lab assignment table
    void store_labAssignment(int id, int grade, int studentId, int labId, std::vector<int> rubricItemIds);

    // Method to store a new row in the rubric item table
    void store_rubricItem(int id, std::string subject, int points, std::vector<int> commentIds);

    // Method to store a new row in the comment table
    void store_comment(int id, std::string comment, int lineNum, std::string filename, int rubricItemId);

private:
    // Reference to database tool that will store the tables
    DBTool * dbtool;

    // Table to store section data
    DBTable * sectionTable;

    // Table to store student data
    DBTable * studentTable;

    // Table to store lab data
    DBTable * labTable;

    // Table to store template data
    DBTable * templateTable;

    // Table to store lab assignment data
    DBTable * labAssignmentTable;

    // Table to store rubric item data
    DBTable * rubricItemTable;

    // Table to store comment data
    DBTable * commentTable;

    // Map of additional tables created on the fly
    // Used to store one to many links from an object
    std::map <std::string, DBTable *> additionalTables;

    // Create a table that stores one to many links
    void create_additional_table(std::vector<int> ids, std::string tableName);

    // Creates main DBTable objects
    void initialize_main_tables();
};

#endif // DBENGINE_H
