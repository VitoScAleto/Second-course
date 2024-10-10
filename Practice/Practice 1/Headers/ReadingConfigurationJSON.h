#ifndef READING_CONFIGURATION_JSON
#define READING_CONFIGURATION_JSON

#include "Headers.h"
#include "Queue.h"

class ReadingJSON
{

private:
    string name;

    int tuples_limit;

    string nameTable1;
    string nameTable2;
    
    string pathToTable1;
    string pathToTable2;

   
    void CreateMainDir(json& j);
    void CreateTable1(json& j);
    void CreateTable2(json& j);
    void CreateCSVFile(json& j, int n);
    
    string ReturnNameObjectFromStructure(int indexObj, json& j);

    json ParseJSON();
    
public:
    void ReadingConfigurationJSON(string pathShemaJSON);

    template <typename T>
    Queue<T> GetColumnsFromSchema(string nameTable);

    string GetNameTable1JSON();
    string GetNameTable2JSON();
    string GetPathToTable1JSON();
    string GetPathToTable2JSON();

   

};



#include "../Source/ReadingConfigurationJSON.cpp"

#endif