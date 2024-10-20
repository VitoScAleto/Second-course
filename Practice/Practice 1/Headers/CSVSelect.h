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

    bool IsValidAfterFROM(LinkedList<string>&  nameTableFromQuery,stringstream& stream);
    int findColumnIndex(const string& header, const string& columnName);
    
    public:

    CSVSelect(ReadingJSON& JSON);

    bool ParseCommandForSelect(LinkedList<string>& nameTableFromQuery, LinkedList<string>& nameColumnFromQuery, stringstream& stream);
    void SelectFromCSV(LinkedList<string>&  nameTableFromQuery, LinkedList<string>& nameColumnFromQuery);

   
};




#include "../Source/CSVSelect.cpp"



#endif