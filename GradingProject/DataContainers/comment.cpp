#include "comment.h"

int Comment::idCount = 0;

Comment::Comment()
{
    ID = idCount;
    idCount += 1;
}


Comment::Comment(string in)
{
    comment = in;
    ID = idCount;
    idCount += 1;
}

Comment::Comment(string in, int line, string file)
{
    comment = in;
    lineNum = line;
    fileName = file;
    ID = idCount;
    idCount += 1;
}

Comment::~Comment()
{

}

string Comment::get_Comment()
{
    return comment;
}

void Comment::change_Comment(string in)
{
    comment = in;
}

void Comment::set_line(int line)
{
    lineNum = line;
}

int Comment::get_line()
{
    return lineNum;
}

void Comment::set_Rubric_Item(RubricItem *ptr)
{
    link = ptr;
}

RubricItem * Comment::get_Rubric_Item()
{
    return link;
}

void Comment::set_fileName(string in)
{
    fileName = in;
}

string Comment::get_fileName()
{
    return fileName;
}

void Comment::set_Id(int id)
{
    ID = id;
}

int Comment::get_Id()
{
    return ID;
}
