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
    //Constructors and destructor
    RubricItem();
    RubricItem(string sub, int pnts);
    ~RubricItem();

    //Getters, setters, and methods to add.
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

    void set_maxP(int p);
    int get_maxP();

    vector <int> get_Comment_Ids();

    vector <Comment *> get_comments();

    static int idCount;

private:
    string subject; //subject of rubric item
    int points; //points off for rubric item
    int maxPoints; //max points rubric tiem is worth
    bool applied; //Whether or no the rubric item was applied
    vector <Comment *> comments; //vector of comments associated with the rubric items
    int ID; //id for database
};


#endif // RUBRICITEM_H
