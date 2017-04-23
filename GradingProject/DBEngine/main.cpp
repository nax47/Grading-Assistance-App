#include <iostream>
#include "dbengine.h"
#include "dbtable.h"
#include "dbtool.h"

int main(int argc, char *argv[])
{
    DBEngine * engine = new DBEngine(new DBTool("ToolDB"));
    std::vector<int> testIds = {7, 4, 5,9};
    engine->store_section(1,testIds, testIds);
    engine->store_student(1, "Nakul Talwar", testIds);
    engine->store_lab(1, 2, 3, 1);
    engine->store_template(1, testIds);
    engine->store_labAssignment(1, 85, 1, 3, testIds);
    engine->store_rubricItem(1, "Style", 9, testIds);
    engine->store_comment(1, "Too much indenting", 57, "testfile.txt", 4);
    engine->get_data();
    return 0;
}
