#include "comment.h"

int Comment::idCount = 0;

//Comment object. Each comment has a comment, line number,
//file name, rubric item, and id associated with it.

//Default contructor that initializes ID and idCount.
Comment::Comment()
{
    ID = idCount;
    idCount += 1;
}

//Constructor to set comment, id, and id count.
Comment::Comment(string in)
{
    comment = in;
    ID = idCount;
    idCount += 1;
}

//Constructor to set comment, line number, file name, id and id count.
Comment::Comment(string in, int line, string file)
{
    comment = in;
    lineNum = line;
    fileName = file;
    ID = idCount;
    idCount += 1;
}

//Destructor
Comment::~Comment()
{

}

//Returns comment.
string Comment::get_Comment()
{
    return comment;
}

//Sets comment.
void Comment::change_Comment(string in)
{
    comment = in;
}

//Sets line number.
void Comment::set_line(int line)
{
    lineNum = line;
}

//Gets line number.
int Comment::get_line()
{
    return lineNum;
}

//Sets rubric item that comment is included in.
void Comment::set_Rubric_Item(RubricItem *ptr)
{
    link = ptr;
}

//Gets rubric item comment is included in.
RubricItem * Comment::get_Rubric_Item()
{
    return link;
}

//Sets file name comment appears on.
void Comment::set_fileName(string in)
{
    fileName = in;
}

//Gets file name comment appears on.
string Comment::get_fileName()
{
    return fileName;
}

//Sets id used for database.
void Comment::set_Id(int id)
{
    ID = id;
}

//Gets id used for database.
int Comment::get_Id()
{
    return ID;
}
