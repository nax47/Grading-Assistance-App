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

TEST(general, RUBRIC_ITEM_TEST)
{
    RubricItem r1("test", 10);
    ASSERT_EQ(r1.get_Subject(), "test");
    r1.set_Subject("new");
    ASSERT_EQ(r1.get_Subject(), "new");
    ASSERT_EQ(r1.get_Points(), 10);
    r1.set_Points(1);
    ASSERT_EQ(r1.get_Points(), 1);


    Comment * cptr = new Comment("comment");
    r1.add_Comment(cptr);
    ASSERT_EQ(r1.get_Comment(0)->get_Comment(), "test comment");

}

TEST(general, LABASSIGNMENT_TEST)
{
    LabAssignment la1;
    Student * stuptr = new Student("john");
    la1.set_Student(stuptr);
    ASSERT_EQ(la1.get_Student()->get_Name(), "john");
    RubricItem * riptr = new RubricItem("test", 10);
    la1.new_RI(riptr);
    ASSERT_EQ(la1.get_RI("test")->get_Subject(), "test");
    Comment * comptr = new Comment("test com");
    la1.add_Comment(comptr, riptr);
    la1.set_Grade(100);
    ASSERT_EQ(la1.get_Grade(), 100);
    Lab * labptr = new Lab();
    labptr->set_ID(1);
    la1.set_Lab(labptr);
    ASSERT_EQ(la1.get_Lab()->get_ID(), 1);

}

TEST(general, STUDENT_TEST)
{
    Student stu("stu");
    ASSERT_EQ(stu.get_Name(), "stu");
    stu.set_Name("new stu");
    ASSERT_EQ(stu.get_Name(), "new stu");
    LabAssignment * labptr = new LabAssignment();
    labptr->set_Grade(100);
    stu.add_Lab(labptr);
    ASSERT_EQ(stu.get_Lab(0)->get_Grade(), 100);

}

int main(int argc, char **argv) {

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
