#ifndef WORK_WITH_FILES_H
#define WORK_WITH_FILES_H

#include "Headers.h"
#include "Queue.h"


void InsertToCSV(string data, string nameTable);

template <typename T>
Queue<T> extractDataFromQuery(string input);

void WorkWithFile_pk_sequence(fs::path nameTable);



#include "../Source/WorkWithFiles.cpp"

#endif