
#include "../Headers/ReadingConfigurationJSON.h"
#include "../Headers/SQLQueryParse.h"


int main()
{

    ReadingJSON JSON;
    
    JSON.ReadingConfigurationJSON("../JSON/schema.json");

    CSVInsert csvInsert(JSON);
    CSVDelete csvDelete(JSON);
    CSVSelect csvSelect(JSON);
    CSVWhere csvWhere(JSON);

    SQLQueryParse myQuery(JSON, csvInsert,csvDelete, csvSelect, csvWhere);
    

    myQuery.Start();

    return 0;
}