#include "comment.h"

Comment::Comment()
{

}


Comment::Comment(string in)
{
    comment = in;
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
