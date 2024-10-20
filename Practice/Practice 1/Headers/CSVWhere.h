#ifndef CSV_WHERE_H
#define CSV_WHERE_H

#include "Headers.h"
#include "ReadingConfigurationJSON.h"
#include "FList.h"

class CSVWhere
{

    private:


    ReadingJSON& JSON;
    
    bool IsValidCommandPostWhere(LinkedList<string>&  nameTableFromQuery, 
                                LinkedList<string>& nameColumnFromQuery);

    bool IsValidCondition(string condition);

    int findColumnIndex(const string& header, const string& columnName);

    struct ParseConditionValue
    {
        string table;  
        string column; 
        string value;
    };
    
    struct ParseConditionNotValue
    {
        string leftTable;
        string leftColumn;
        string rightTable;
        string rightColumn;
    };

    bool FunParseConditionNotValues(const string& condition, ParseConditionNotValue& parsed);
    void FunParseConditionValues(const string& condition, ParseConditionValue& parsed);

                              
    public:

    LinkedList<string> conditions;
    LinkedList<string> operators;
    LinkedList<string> ss;



    CSVWhere(ReadingJSON& JSON);

    void Filtration();

    void StartWhere(LinkedList<string>&  nameTableFromQuery, 
                    LinkedList<string>& nameColumnFromQuery,
                    stringstream& stream);

    void ParseWhereQuery(string whereClause);



};


#include "../Source/CSVWhere.cpp"

#endif