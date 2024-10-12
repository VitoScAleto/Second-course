
#include "../Headers/ReadingConfigurationJSON.h"
#include "../Headers/SQLQueryParse.h"
#include "../Headers/CSVInsert.h"

int main()
{
    ReadingJSON JSON;
    
    JSON.ReadingConfigurationJSON("../JSON/schema.json");

    CSVInsert csvInsert(JSON);
    CSVDelete csvDelete(JSON);
    CSVSelect csvSelect(JSON);

    SQLQueryParse myQuery(JSON, csvInsert,csvDelete, csvSelect);
    

    myQuery.Start();

    return 0;
}