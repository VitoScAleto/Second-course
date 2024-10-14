#ifndef CSV_SELECT_H
#define CSV_SELECT_H

#include "Headers.h"
#include "Queue.h"
#include "ReadingConfigurationJSON.h"
#include "FList.h"


class CSVSelect
{
    private:

    ReadingJSON& JSON;

    bool ParsePostQuery(const string nameTable1, const string nameTable2,stringstream& stream);

    public:

    CSVSelect(ReadingJSON& JSON);

    bool ParseCommandForSelect(string& nameTable1,string& nameTable2,string& nameColumn1, string& nameColumn2,stringstream& stream);
    void SelectFromCSV(string& nameTable1,string& nameTable2,string& nameColumn1, string& nameColumn2);
   
};




#include "../Source/CSVSelect.cpp"



#endif