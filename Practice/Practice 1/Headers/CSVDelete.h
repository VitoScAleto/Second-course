#ifndef CSV_DELETE_H
#define CSV_DELETE_H

#include "Headers.h"
#include "Queue.h"
#include "ReadingConfigurationJSON.h"
#include "FList.h"

class CSVDelete
{

    private:

      ReadingJSON& JSON;

    public:

    CSVDelete(ReadingJSON& JSON);

    void DeleteStart(stringstream& stream);

    void ParseCommandForDelete(string& nameTable, string& nameColumn, string& equalSym, string& value,stringstream& stream);
    void DeleteFromCSV(string nameTable, string nameColumn, string valuesToDelete);

};



#include "../Source/CSVDelete.cpp"

#endif