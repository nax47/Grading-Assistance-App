#include <iostream>
#include "dbengine.h"
#include "dbtable.h"
#include "dbtool.h"

int main(int argc, char *argv[])
{
    DBEngine * engine = new DBEngine(new DBTool("TestDB4"));
    std::vector<int> testIds = {};
    std::vector<int> testIds1 = {1,2};
    std::vector<int> testIds2 = {1};
    std::vector<int> testIds3 = {2};
    engine->store_section(1,testIds1, testIds1);
    engine->store_section(47,testIds, testIds);
    engine->store_student(1, "Nakul Talwar", testIds2);
    engine->store_student(2, "Chris Bennett", testIds3);
    engine->store_lab(1, 1, 1, 1);
    engine->store_lab(2, 1, 2, 1);
    engine->store_template(1, testIds2);
    engine->store_labAssignment(1, 85, 1, 1, testIds);
    engine->store_labAssignment(2, 75, 2, 1, testIds);
    engine->store_rubricItem(1, "Style", 9, testIds2);
    engine->store_comment(1, "Too much indenting", 57, "testfile.txt", 1);
    delete engine;
    engine = new DBEngine(new DBTool("TestDB4"));
    std::vector<Section *> testSections;
    std::vector<Student *> students;
    testSections = engine->get_sections();
    students = engine->get_students();
    for(int i = 0; i<testSections.size(); i++){
        std::cout << "Section: " << std::to_string(testSections.at(i)->get_Id())<< std::endl;
    }

    for(int i = 0; i<students.size(); i++){
        std::cout << "Student: " << std::to_string(students.at(i)->get_Id())<< " Name: " << students.at(i)->get_Name() << std::endl;
    }
    return 0;
}
