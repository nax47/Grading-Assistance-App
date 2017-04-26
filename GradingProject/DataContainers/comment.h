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
    Comment(string in, int line, string file);
    ~Comment();

    string get_Comment();
    void change_Comment(string in);

    void set_line(int line);
    int get_line();

    void set_Rubric_Item(RubricItem * ptr);
    RubricItem * get_Rubric_Item();

    void set_fileName(string in);
    string get_fileName();

    void set_Id(int id);
    int get_Id();

    static int idCount;

private:
    string comment;
    int lineNum;
    string fileName;
    RubricItem * link;
    int ID;
};


#endif // COMMENT_H
