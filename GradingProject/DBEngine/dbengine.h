#ifndef DBENGINE_H
#define DBENGINE_H

#include "dbtable.h"
#include "dbtool.h"

class DBTool;

class DBEngine{
public:
    DBEngine(DBTool * dbtool);
    ~DBEngine();
private:
    DBTool * dbtool;
};

#endif // DBENGINE_H
