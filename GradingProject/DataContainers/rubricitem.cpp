#include "rubricitem.h"

//Rubric item object.
//Each item has a subject, points off, max points, whether or
//not the item was applied to the assignment, a vector of comments, and an
//id associated with it.

int RubricItem::idCount = 0;

//Constructor that sets id, id count, and applied to false;
RubricItem::RubricItem()
{
    ID = idCount;
    idCount += 1;
    applied = false;
}

//Constructor that sets id, id count, applied to false,
//subject, and points
RubricItem::RubricItem(string sub, int pnts)
{
    subject = sub;
    points = pnts;
    ID = idCount;
    idCount += 1;
    applied = false;
}

//Destructor.
RubricItem::~RubricItem()
{

}

//Sets subject.
void RubricItem::set_Subject(string sub)
{
    subject = sub;
}

//Gets subject.
string RubricItem::get_Subject()
{
    return subject;
}

//Sets points.
void RubricItem::set_Points(int point)
{
    points = point;
}

//Gets points.
int RubricItem::get_Points()
{
    return points;
}

//Gets comment at given index.
Comment * RubricItem::get_Comment(int num)
{
    return comments.at(num);
}

//Adds new comment to vector.
void RubricItem::add_Comment(Comment *newCom)
{
    comments.push_back(newCom);
}

//Deletes comment at given index in vector
void RubricItem::delete_Comment(int num)
{
    delete comments.at(num);
}

//Sets applied boolean.
void RubricItem::set_Applied(bool in)
{
    applied = in;
}

//Gets applied.
bool RubricItem::get_Applied()
{
    return applied;
}

//Sets max points
void RubricItem::set_maxP(int p)
{
    maxPoints = p;
}

//Gets max points.
int RubricItem::get_maxP()
{
    return maxPoints;
}

//Sets id for database.
void RubricItem::set_Id(int id)
{
    ID = id;
}

//Gets id for database.
int RubricItem::get_Id()
{
    return ID;
}

//Gets ids for comments associated with rubric item.
vector <int> RubricItem::get_Comment_Ids(){

    vector<int> ids;

    for(int i=0; i<comments.size(); i++){
        ids.push_back(comments.at(i)->get_Id());
    }

    return ids;
}

//Returns entire vector of comments.
vector <Comment *> RubricItem::get_comments(){
    return comments;
}
