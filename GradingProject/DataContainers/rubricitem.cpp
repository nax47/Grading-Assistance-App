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
