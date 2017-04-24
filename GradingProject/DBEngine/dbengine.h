#ifndef DBENGINE_H
#define DBENGINE_H

#include "dbtable.h"
#include "dbtool.h"
#include <vector>
#include <map>
#include "../DataContainers/rubricitem.h"
#include "../DataContainers/template.h"
#include "../DataContainers/student.h"
#include "../DataContainers/lab.h"
#include "../DataContainers/comment.h"
#include "../DataContainers/section.h"
#include "../DataContainers/labassignment.h"


class DBTool;
class DBTable;

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

    // Method to recreate section objects from table data
    void restore_section_data(char **data);

    // Method to recreate student objects from table data
    void restore_student_data(char **data);

    // Method to recreate lab objects from table data
    void restore_lab_data(char **data);

    // Method to recreate template objects from table data
    void restore_template_data(char **data);

    // Method to recreate rubric item objects from table data
    void restore_rubricItem_data(char **data);

    // Method to recreate lab assignment objects from table data
    void restore_labAssignment_data(char **data);

    // Method to recreate comment objects from table data
    void restore_comment_data(char **data);

    // Method to restore data from an additional  table
    void restore_additional_table_data(std::string tableName, char **data);

    void get_data();

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

    // Map to temporarily store sections while recreating data structures
    std::map <int, Section *> sections;

    // Map to temporarily store students while recreating data structures
    std::map <int, Student *> students;

    // Map to temporarily store labs while recreating data structures
    std::map <int, Lab *> labs;

    // Map to temporarily store templates while recreating data structures
    std::map <int, Template *> templates;

    // Map to temporarily store labAssignments while recreating data structures
    std::map <int, LabAssignment *> labAssignments;

    // Map to temporarily store rubricItems while recreating data structures
    std::map <int, RubricItem *> rubricItems;

    // Map to temporarily store comments while recreating data structures
    std::map <int, Comment *> comments;

    // Create a table that stores one to many links
    void create_additional_table(std::vector<int> ids, std::string tableName);

    // Creates main DBTable objects
    void initialize_main_tables();
};

#endif // DBENGINE_H
