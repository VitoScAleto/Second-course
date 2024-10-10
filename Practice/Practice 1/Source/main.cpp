
#include "../Headers/ReadingConfigurationJSON.h"
#include "../Headers/SQLQueryParse.h"
#include "../Headers/CSVInsert.h"

int main()
{
    ReadingJSON JSON;
    
    JSON.ReadingConfigurationJSON("../JSON/schema.json");

    CSVInsert csvInsert(JSON);
    CSVDelete csvDelete(JSON);

    SQLQueryParse myQuery(JSON, csvInsert,csvDelete);
    

    myQuery.Start();

    return 0;
}