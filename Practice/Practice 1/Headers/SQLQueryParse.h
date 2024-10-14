#ifndef SQL_QUERY_PARSE_H
#define SQL_QUERY_PARSE_H

#include "Headers.h"
#include "CSVInsert.h"
#include "ReadingConfigurationJSON.h"
#include "CSVDelete.h"
#include "CSVSelect.h"
#include "CSVWhere.h"

class SQLQueryParse
{
    private:

    ReadingJSON& JSON;
    CSVInsert& csvInsert;
    CSVDelete& csvDelete;
    CSVSelect& csvSelect;
    CSVWhere& csvWhere;

    bool SearcWhereInQuery(stringstream& stream,const string searchString);
    bool IsValidQueryForSelect(stringstream& stream);
    
    public:

    SQLQueryParse(ReadingJSON& JSON, CSVInsert& csvInsert, CSVDelete& csvDelete, CSVSelect& csvSelect, CSVWhere& csvWhere);
    
    void Start();
    void SelectAndWhereStart(stringstream& stream);
    void SQLInsert(stringstream& stream);
    void SQLDelete(stringstream& stream);
};


#include "../Source/SQLQueryParse.cpp"

#endif