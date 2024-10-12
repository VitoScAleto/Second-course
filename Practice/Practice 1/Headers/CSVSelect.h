#ifndef CSV_SELECT_H
#define CSV_SELECT_H

#include "Headers.h"
#include "Queue.h"
#include "ReadingConfigurationJSON.h"
#include "FList.h"
#include "vector"
class CSVSelect
{
    private:

    ReadingJSON& JSON;

    public:

    CSVSelect(ReadingJSON& JSON);

    void SelectStart(stringstream& stream);

    void ParseCommandForSelect(string& nameTable1,string& nameTable2,string& nameColumn1, string& nameColumn2,stringstream& stream);
    void SelectFromCSV(string& nameTable1,string& nameTable2,string& nameColumn1, string& nameColumn2);

};




#include "../Source/CSVSelect.cpp"



#endif