/*********************************************************************

Copyright (C) 2015 Jeffrey O. Pfaffmann

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

Modified by Nakul Talwar in April 2017

*********************************************************************/

#include "dbtable.h"

 // Default constructor that is only called when the software
 // developer uses the package incorrectly.
DBTable::DBTable() {
    std::cerr << "Table name must be provided "
              << "for DBTable Class during "
              << "construction.\n"
              << "Exiting\n";
    exit(-1);
}

 // Constructor taking a pointer to the DB tool and name
 // of the table that will be represented by this class.
DBTable::DBTable(DBTool      *db,
                 std::string  name,
                 std::string createString) {

    // Store table name and reference to db.
    curr_db     = db;
    table_name  = name;

    // Register the different sql calls for the
    // parent class.
    store_exist_sql();
    store_drop_sql();
    store_size_sql();

    sql_create = createString;
    sql_add_row = "";
    sql_select_all = "";

    //Reconstitute data from existing table
    //reconstitute();

    //Delete existing database table
    drop();

    // must build table sepparately so new
    // sql can be properly registered
    build_table();
}

 // This should be called by the child constructor but
 // is used to build a table in the database if the table
 // does not exist.
void DBTable::build_table() {

    // determine if table exists
    exist();

    if (!table_exists) {

        // if it does not exist create table
        create();
    }
}

 // Deconstructor
DBTable::~DBTable() {
    // std::cerr << "Deconstructing table object "
    // 	    << table_name
    // 	    << std::endl;
}

 // SQL used to get a list of all tables in the DB tool.
void DBTable::store_template_sql() {

    sql_template =  "SELECT name ";
    sql_template += "FROM   sqlite_master ";
    sql_template += "WHERE";
    sql_template += "    type = \"table\"";
    sql_template += ";";

}

 // SQL used to determine if a specific table exists
 // in the database.
void DBTable::store_exist_sql() {

    sql_exist  = "SELECT count(*) ";
    sql_exist += "FROM   sqlite_master ";
    sql_exist += "WHERE";
    sql_exist += "    type = \"table\" ";
    sql_exist += "and name = \"" + table_name + "\"";
    sql_exist += ";";

}

 // SQL for removing the table from the database.
void DBTable::store_drop_sql() {

    sql_drop =  "DROP TABLE ";
    sql_drop += table_name;
    sql_drop += ";";

}

 // SQL to determine number of records in the database.
void DBTable::store_size_sql() {

    sql_size =  "SELECT count(*) ";
    sql_size += "FROM ";
    sql_size += table_name;
    sql_size += ";";

}

 // Method for calling the template DB SQL above.
int DBTable::dbtemplate() {

    // Initialize local variables.
    int   retCode = 0;
    char *zErrMsg = 0;

    // Call sqlite to run the SQL call using the
    // callback to store any results.
    retCode = sqlite3_exec(curr_db->db_ref(),
                           sql_template.c_str(),
                           cb_template,
                           this,
                           &zErrMsg          );

    if( retCode != SQLITE_OK ){

        std::cerr << sql_template
                  << std::endl;

        std::cerr << "SQL error: "
                  << zErrMsg
                  << std::endl;

        sqlite3_free(zErrMsg);
    }

    return retCode;
}

int cb_template(void  *data,
                int    argc,
                char **argv,
                char **azColName){

    if(argc < 1) {
        std::cerr << "No data presented to callback "
                  << "argc = " << argc
                  << std::endl;
    }

    return 0;
}

 // Determine if table exists.
bool DBTable::exist() {

    // Initialize local variables.
    int   retCode = 0;
    char *zErrMsg = 0;

    // Call sqlite to run the SQL call using the
    // callback to store any results.  The parameters
    // are identified as follows:
    // 1. Provide reference to sqlite object in dbtool.
    // 2. Provide the SQL command as a C string.
    // 3. Provide pointer to callback function coded below.
    // 4. Pointer to the DBTable object.
    // 5. Pointer to varible where sqlite will place error code.
    retCode = sqlite3_exec(curr_db->db_ref(),
                           sql_exist.c_str(),
                           cb_exist,
                           this,
                           &zErrMsg          );

    // Process return code.
    if( retCode != SQLITE_OK ){

        std::cerr << sql_exist
                  << std::endl;

        std::cerr << "SQL error: "
                  << zErrMsg
                  << std::endl;

        sqlite3_free(zErrMsg);
    }

    return retCode;
}

 // callback to determine if table exists.  SQLite
 // will pass the results of the call and this function
 // will manipulate and make changes to the DBTable object.
int cb_exist(void  *data,        // pointer to the DBTable object.
             int    argc,        // number of data columns
             char **argv,        // the actual data columns
             char **azColName){  // the data column names


    if(argc != 1) {

        // If call fails, generate error message.
        std::cerr << "More than one item returned "
                  << "argc = " << argc
                  << std::endl;
    } else {

        DBTable *obj = (DBTable *) data;

        if (atoi(argv[0])) {
            //std::cerr << "setting exists\n";
            obj->set_exists();
        } else {
            //std::cerr << "unsetting exists\n";
            obj->unset_exists();
        }
    }


    return 0;
}

 // Create the db table.
bool DBTable::create() {

    // Initialize local variables.
    int   retCode = 0;
    char *zErrMsg = 0;

    // Call sqlite to run the SQL call using the
    // callback to store any results.
    retCode = sqlite3_exec(curr_db->db_ref(),
                           sql_create.c_str(),
                           cb_create,
                           this,
                           &zErrMsg          );

    // Process a failed call.
    if( retCode != SQLITE_OK ){

        std::cerr << sql_create
                  << std::endl;

        std::cerr << "SQL error: "
                  << zErrMsg
                  << std::endl;

        sqlite3_free(zErrMsg);
    }

    // Return the code.
    return retCode;
}

 // The callback after the table is created.   SQLite
 // will pass the results of the call and this function
 // will manipulate and make changes to the DBTable object.
int cb_create(void  *data,
              int    argc,
              char **argv,
              char **azColName){

    // Create failed, generate error message.
    if(argc < 1) {
        std::cerr << "No data presented to callback "
                  << "argc = " << argc
                  << std::endl;
    }

    // Commented code prints information returned by
    // sqlite.

    // std::cout << "------------------------------\n";
    // std::cout << obj->get_name()
    // 	    << std::endl;

    // int i;
    // for(i = 0; i < argc; i++){
    //   std::cout << azColName[i]
    // 	      << " = "
    // 	      <<  (argv[i] ? argv[i] : "NULL")
    // 	      << std::endl;
    // }

    // Return the code.
    return 0;
}

 // Removes the db table from the database.
bool DBTable::drop() {

    // Initialize local variables.
    int   retCode = 0;
    char *zErrMsg = 0;

    // Call sqlite to run the SQL call using the
    // callback to store any results.
    retCode = sqlite3_exec(curr_db->db_ref(),
                           sql_drop.c_str(),
                           cb_drop,
                           this,
                           &zErrMsg          );

    // Process a failed call.
    if( retCode != SQLITE_OK ){

        std::cerr << sql_drop
                  << std::endl;

        std::cerr << "SQL error: "
                  << zErrMsg
                  << std::endl;

        sqlite3_free(zErrMsg);
    }

    //
    return retCode;
}

 // The callback after the table is droped.   SQLite
 // will pass the results of the call and this function
 // will manipulate and make changes to the DBTable object.
int cb_drop(void  *data,
            int    argc,
            char **argv,
            char **azColName){


    // Table not dropped, generate error message.
    if(argc < 1) {
        std::cerr << "No data presented to callback "
                  << "argc = " << argc
                  << std::endl;
    }

    // std::cout << "------------------------------\n";
    // std::cout << obj->get_name()
    // 	    << std::endl;

    // int i;
    // for(i = 0; i < argc; i++){
    //   std::cout << azColName[i]
    // 	      << " = "
    // 	      <<  (argv[i] ? argv[i] : "NULL")
    // 	      << std::endl;
    // }

    return 0;
}

 // Determines the number of rows in the table.
int DBTable::size() {

    // Initialize local variables.
    int   retCode = 0;
    char *zErrMsg = 0;

    // Call sqlite to run the SQL call using the
    // callback to store any results.
    retCode = sqlite3_exec(curr_db->db_ref(),
                           sql_size.c_str(),
                           cb_size,
                           this,
                           &zErrMsg          );

    // Process a failed call.
    if( retCode != SQLITE_OK ){

        std::cerr << sql_size
                  << std::endl;

        std::cerr << "SQL error: "
                  << zErrMsg
                  << std::endl;

        sqlite3_free(zErrMsg);
    }

    // Return the number of rows in table.
    return row_cnt;
}

 // The callback after the size is computed.   SQLite
 // will pass the results of the call and this function
 // will manipulate and make changes to the DBTable object.
int cb_size(void  *data,
            int    argc,
            char **argv,
            char **azColName){

    // If no data is presented generate error message.
    if(argc < 1) {
        std::cerr << "No data presented to callback "
                  << "argc = " << argc
                  << std::endl;
    } else {

        // Store size in object.
        DBTable *obj = (DBTable *) data;
        obj->set_size(atoi(argv[0]));
    }

    return 0;
}

// Get table name
std::string DBTable::get_name() {
    return table_name;
}

// Add specific row to table
// The SQL statement specific to this table and row will be
// passed in as a string
bool DBTable::add_row(std::string add_row){
    int   retCode = 0;
    char *zErrMsg = 0;

    sql_add_row = add_row;

    //std::cout << sql_add_row << std::endl;

    retCode = sqlite3_exec(curr_db->db_ref(),
                           sql_add_row.c_str(),
                           cb_add_row,
                           this,
                           &zErrMsg          );

    if( retCode != SQLITE_OK ){

        std::cerr << table_name
                  << " template ::"
                  << std::endl
                  << "SQL error: "
                  << zErrMsg;

        sqlite3_free(zErrMsg);
    }

    return retCode;
}

// The callback after a row is added to the table.   SQLite
// will pass the results of the call and this function
// will manipulate and make changes to the DBTable object.
int cb_add_row(void  *data,
                int    argc,
                char **argv,
                char **azColName)
{

    std::cerr << "cb_add_row being called\n";

    if(argc < 1) {
        std::cerr << "No data presented to callback "
                  << "argc = " << argc
                  << std::endl;
    }

    int i;

    DBTable *obj = (DBTable *) data;

    std::cout << "------------------------------\n";
    std::cout << obj->get_name()
              << std::endl;

    for(i = 0; i < argc; i++){
        std::cout << azColName[i]
                     << " = "
                     <<  (argv[i] ? argv[i] : "NULL")
                      << std::endl;
    }

    return 0;
}

// Select all rows from the table.
// Data from the tables can be obtained one row
// at a time from the callback cb_select_all
bool DBTable::select_all() {

    int   retCode = 0;
    char *zErrMsg = 0;

    sql_select_all  = "SELECT * FROM ";
    sql_select_all += table_name;
    sql_select_all += ";";

    retCode = sqlite3_exec(curr_db->db_ref(),
                           sql_select_all.c_str(),
                           cb_select_all,
                           this,
                           &zErrMsg          );

    if( retCode != SQLITE_OK ){

        std::cerr << table_name
                  << " template ::"
                  << std::endl
                  << "SQL error: "
                  << zErrMsg;

        sqlite3_free(zErrMsg);
    }

    return retCode;
}

// The callback after all the rows in the table are selected.
// SQLite will pass the results of the call and this function
// will manipulate and make changes to the DBTable object.
int cb_select_all(void  *data,
                   int    argc,
                   char **argv,
                   char **azColName)
{

    std::cerr << "cb_select_all being called\n";

    if(argc < 1) {
        std::cerr << "No data presented to callback "
                  << "argc = " << argc
                  << std::endl;
    }

    int i;

    DBTable *obj = (DBTable *) data;

    std::cout << "------------------------------\n";
    std::cout << obj->get_name()
              << std::endl;

    for(i = 0; i < argc; i++){
        std::cout << azColName[i]
                     << " = "
                     <<  (argv[i] ? std::string(argv[i]) : "NULL")
                      << std::endl;
    }

    return 0;
}
