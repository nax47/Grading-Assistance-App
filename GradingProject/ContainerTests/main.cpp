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

TEST(general, LAB_TEST)
{
    Lab l1;
    Section * sptr1 = new Section();
    Template * tptr1 = new Template();
    sptr1->set_Id(1);
    RubricItem * ript = new RubricItem("test",10);
    tptr1->add_RI(ript);
    l1.set_Section(sptr1);
    l1.set_Template(tptr1);


    ASSERT_EQ(l1.get_Section()->get_Id(), 1) << "get section > get section id";
    Template * temp1 = l1.get_Template();
    RubricItem * ri1 = temp1->get_RI(0);
    string test1 = ri1->get_Subject();
    ASSERT_EQ(test1, "test") << "get template > get Rubric Item > get Subject";


}

int main(int argc, char **argv) {

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
