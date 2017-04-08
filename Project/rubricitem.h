#ifndef RUBRICITEM_H
#define RUBRICITEM_H

#include <iostream>
#include <string>
#include <vector>
#include "comment.h"

using namespace std;

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

private:
    string subject;
    int points;
    vector <Comment *> comments;

};

#endif // RUBRICITEM_H
