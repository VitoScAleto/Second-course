#ifndef SQL_QUERY_PARSE_H
#define SQL_QUERY_PARSE_H

#include "Headers.h"
#include "CSVInsert.h"
#include "ReadingConfigurationJSON.h"
#include "CSVDelete.h"


class SQLQueryParse
{
    private:

    ReadingJSON& JSON;
    CSVInsert& csvInsert;
    CSVDelete& csvDelete;

    public:

    SQLQueryParse(ReadingJSON& JSON, CSVInsert& csvInsert, CSVDelete& csvDelete);
    
    void Start();

    void SQLInsert(stringstream& stream);

    void SQLDelete(stringstream& stream);
};


#include "../Source/SQLQueryParse.cpp"

#endif