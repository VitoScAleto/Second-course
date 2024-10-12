#ifndef READING_CONFIGURATION_JSON
#define READING_CONFIGURATION_JSON

#include "Headers.h"
#include "Queue.h"
#include "FList.h"

class ReadingJSON
{

private:
    string name;

    int tuples_limit;
    
    string pathToTable1;
    string pathToTable2;

    LinkedList <string> nameTables;
    LinkedList <string> nameColumns;
   
    void CreateMainDir(json& j);
    void CreateTable(json& j);
    void CreateCSVFile(json& j);

    json ParseJSON();

    void FillingTheListFromTheSchema();
public:
    void ReadingConfigurationJSON(const string pathShemaJSON);

    template <typename T>
    Queue<T> GetColumnsFromSchema(const string nameTable);
    bool IsValidTable(const string nameTable) ;   
};



#include "../Source/ReadingConfigurationJSON.cpp"

#endif