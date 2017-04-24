#ifndef RUBRICITEM_H
#define RUBRICITEM_H

#include <iostream>
#include <string>
#include <vector>
#include "comment.h"

using namespace std;

class Comment;

class RubricItem
{
public:
    RubricItem();
    RubricItem(string sub, int pnts);
    ~RubricItem();

    void set_Subject(string sub);
    string get_Subject();

    void set_Points(int point);
    int get_Points();

    Comment * get_Comment(int num);
    void add_Comment(Comment * newCom);
    void delete_Comment(int num);

    void set_Applied(bool in);
    bool get_Applied();

    void set_Id(int id);
    int get_Id();

    vector <int> get_Comment_Ids();

    vector <Comment *> get_comments();

private:
    string subject;
    int points;
    bool applied;
    vector <Comment *> comments;
    int ID;
    //static int idCount;
};

//int RubricItem::idCount = 0;

#endif // RUBRICITEM_H
