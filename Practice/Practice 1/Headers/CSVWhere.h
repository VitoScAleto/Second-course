#ifndef CSV_WHERE_H
#define CSV_WHERE_H

#include "Headers.h"
#include "ReadingConfigurationJSON.h"
#include <regex>
#include "FList.h"

class CSVWhere
{

    private:

    ReadingJSON& JSON;
    
    bool IsValidCommandPostWhere(string nameTable1,string nameTable2,string nameColumn1, string nameColumn2);
    bool IsValidCondition( string condition);
    public:

    LinkedList<string> conditions;
    LinkedList<string> operators;

    CSVWhere(ReadingJSON& JSON);

    void StartWhere(string& nameTable1,string& nameTable2,string& nameColumn1, string& nameColumn2,stringstream& stream);
    void ParseWhereQuery(stringstream& stream);



};





#include "../Source/CSVWhere.cpp"

#endif