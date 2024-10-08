#ifndef WORK_WITH_FILES_H
#define WORK_WITH_FILES_H

#include "Headers.h"
#include "Queue.h"
#include "FList.h"



void WorkWithFile_pk_sequence(string nameTable);

void WorkWithCSV(string data, string nameTable);

template <typename T>
Queue<T> extractDataFromQuery(string input);


class CSV
{
    private:

    int numberColumns;

    string value;

    int max_tuples;

    public:

    CSV();

    void WriteToCSV(string data, string nameTable);
    int CountElementInCSV(string nameTable);
    int WorkWithFile_pk_sequence(string nameTable);
    
};



#include "../Source/WorkWithFiles.cpp"

#endif