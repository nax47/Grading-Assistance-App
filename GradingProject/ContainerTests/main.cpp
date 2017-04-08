#include <iostream>
#include <iostream>
#include <string>
#include "gtest/gtest.h"
#include "../DataContainers/comment.h"
#include "../DataContainers/lab.h"
#include "../DataContainers/labassignment.h"
#include "../DataContainers/rubricitem.h"
#include "../DataContainers/section.h"
#include "../DataContainers/student.h"
#include "../DataContainers/template.h"

using namespace std;



class ReferanceTest : public ::testing::Test {

protected:


    ReferanceTest()
    {

    }

    virtual ~ReferanceTest()
    {

    }

    virtual void SetUp()
    {

    }

    virtual void TearDown()
    {

    }

};

TEST(general, COMMENT_TEST)
{
    Comment c1("new comment");
    ASSERT_EQ(c1.get_Comment(), "new comment") << "special comment constructor stores comment string";
    c1.set_line(24);
    ASSERT_EQ(c1.get_line(), 24);
    RubricItem * temp = new RubricItem("test", 10);
    c1.set_Rubric_Item(temp);
    ASSERT_EQ(c1.get_Rubric_Item(), temp);
    ASSERT_EQ(c1.get_Rubric_Item()->get_Subject(), "test");
    ASSERT_EQ(c1.get_Rubric_Item()->get_Points(), 10);
}


int main(int argc, char **argv) {

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
