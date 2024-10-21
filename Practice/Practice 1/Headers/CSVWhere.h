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
    bool FunParseConditionValues(const string& condition, ParseConditionValue& parsed);

    void FunTable_Table(string& pathToFinishFiltrationFile, ParseConditionNotValue& parseNotValue);     

    void FunTable_value(string& pathToFinishFiltrationFile,
                             ParseConditionNotValue& parseNotValue, 
                                ParseConditionValue& parseWithValue);     
                                
    void FunValue_value(string& pathToFinishFiltrationFile, 
                                ParseConditionValue& parseWithValue1,
                                ParseConditionValue& parseWithValue2);                
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