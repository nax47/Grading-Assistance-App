#ifndef COMMENT_H
#define COMMENT_H

#include <iostream>
#include <string>
#include "rubricitem.h"

using namespace std;

class RubricItem;

class Comment
{
public:
    Comment();
    Comment(string in);
    ~Comment();

    string get_Comment();
    void change_Comment(string in);

    void set_line(int line);
    int get_line();

    void set_Rubric_Item(RubricItem * ptr);
    RubricItem * get_Rubric_Item();


private:
    string comment;
    int lineNum;
    RubricItem * link;


};

#endif // COMMENT_H
