#include "rubricitem.h"

RubricItem::RubricItem()
{

}

RubricItem::RubricItem(string sub, int pnts)
{
    subject = sub;
    points = pnts;
}

RubricItem::~RubricItem()
{

}

void RubricItem::set_Subject(string sub)
{
    subject = sub;
}

string RubricItem::get_Subject()
{
    return subject;
}

void RubricItem::set_Points(int point)
{
    points = point;
}

int RubricItem::get_Points()
{
    return points;
}

Comment * RubricItem::get_Comment(int num)
{
    return comments.at(num);
}

void RubricItem::add_Comment(Comment *newCom)
{
    comments.push_back(newCom);
}

void RubricItem::delete_Comment(int num)
{
    delete comments.at(num);
}

void RubricItem::set_Applied(bool in)
{
    applied = in;
}

bool RubricItem::get_Applied()
{
    return applied;
}

void RubricItem::set_maxP(int p)
{
    maxPoints = p;
}

int RubricItem::get_maxP()
{
    return maxPoints;
}

void RubricItem::set_Id(int id)
{
    ID = id;
}

int RubricItem::get_Id()
{
    return ID;
}

vector <int> RubricItem::get_Comment_Ids(){

    vector<int> ids;

    for(int i=0; i<comments.size(); i++){
        ids.push_back(comments.at(i)->get_Id());
    }

    return ids;
}

vector <Comment *> RubricItem::get_comments(){
    return comments;
}
