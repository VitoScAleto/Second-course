#ifndef WORK_WITH_FILES_H
#define WORK_WITH_FILES_H

#include "Headers.h"
#include "Queue.h"


void InsertToCSV(string data, string pathToCSV);

template <typename T>
Queue<T> extractDataFromQuery(string input);





#include "../Source/WorkWithFiles.cpp"

#endif