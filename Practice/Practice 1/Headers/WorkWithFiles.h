#ifndef WORK_WITH_FILES_H
#define WORK_WITH_FILES_H

#include "Headers.h"
#include "Queue.h"
#include "DoubDynArray.h"


void WriteToCSVFileIntoArray(string data, string nameTable);

void WorkWithFile_pk_sequence(string nameTable);

void WorkWithCSV(string data, string nameTable);

template <typename T>
Queue<T> extractDataFromQuery(string input);


template <typename T>

DoubDynArray<T> ReadingCSVFileIntoArray(string data, string nameTable);


#include "../Source/WorkWithFiles.cpp"

#endif