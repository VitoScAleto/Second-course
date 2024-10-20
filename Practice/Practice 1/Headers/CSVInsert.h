#ifndef CSV_INSERT_H
#define CSV_INSERT_H

#include "Headers.h"
#include "Queue.h"
#include "ReadingConfigurationJSON.h"

class CSVInsert
{
    private:

    int numberElementInCSV;

    ReadingJSON& JSON;
    
    public:

    CSVInsert(ReadingJSON& JSON);

    string nameTableFromQuery;

    void GetNameTableFromQuery(string nameTable);

    template <typename T>
    void extractDataFromQuery(LinkedList<T>& listQuery, string input) ;

    void InsertValuesFromQuery(string data);

    int CountElementInCSV(string nameTable);
    
    int WorkWithFile_pk_sequence(string nameTable);
    
    void WriteToCSV(stringstream& stream);

};


#include "../Source/CSVInsert.cpp"







#endif

