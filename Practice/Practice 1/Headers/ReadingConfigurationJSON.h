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
    
    string pathToTable1;
    string pathToTable2;

    LinkedList <string> nameTables;
    LinkedList <string> nameColumns;
   
    void CreateMainDir(json& j);
    void CreateTable(json& j);
    void CreateCSVFile(json& j);

    json ParseJSON();

    string listFilesInDirectory(const string nameTable);
    
    void FillingTheListFromTheSchema();
public:
    
    string GetNameMainDir();

    void ReadingConfigurationJSON(const string pathShemaJSON);

    string IsValidTuplesLimitInCSV(string nameTable);

    template <typename T>
    Queue<T> GetColumnsFromSchema(const string nameTable);
    bool IsValidTable(const string nameTable) ;   
};



#include "../Source/ReadingConfigurationJSON.cpp"

#endif