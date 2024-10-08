#ifndef READING_CONFIGURATION_JSON
#define READING_CONFIGURATION_JSON

#include "Headers.h"

json ParseJSON();

class ReadingJSON
{

private:

    string name;
    string nameTable1;
    string nameTable2;

public:

    void CreateMainDir(json& j);
    void CreateTable1(json& j);
    void CreateTable2(json& j);
    void CreateCSVFile(json& j, int n);
    string ReturnNameObjectFromStructure(int indexObj, json& j);

};


void ReadingConfigurationJSON();






#include "../Source/ReadingConfigurationJSON.cpp"

#endif