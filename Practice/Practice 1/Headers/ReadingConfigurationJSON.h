#ifndef READING_CONFIGURATION_JSON
#define READING_CONFIGURATION_JSON

#include "Headers.h"
#include "Queue.h"
#include "FList.h"

class ReadingJSON
{

private:
    string nameMainDirJSON;
    
    int tuples_limit;

    LinkedList <string> nameTablesJSON;
    LinkedList <string> nameColumnsJSON;
   
    void CreateMainDir(json& j);
    void CreateTable(json& j);
    void CreateCSVFile(json& j);

    json ParseJSON();


    void FillingTheListTableFromTheSchema();
    void FillingTheListColumnsFromTheSchema(string nameTable);

public:
    
    string GetNameMainDir();

    void ReadingConfigurationJSON(const string pathShemaJSON);

    bool IsValidTable(const string nameTable);   

    bool IsValidColumns(const string nameTable, const string nameColumn);
    
    template <typename T>
    void GetColumnsFromSchema(LinkedList<T>& List,const string nameTable);
};



#include "../Source/ReadingConfigurationJSON.cpp"

#endif