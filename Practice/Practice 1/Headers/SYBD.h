#ifndef SYBD_H
#define SYBD_H

#include "Headers.h"
#include "WorkWithFiles.h"

string TruncateInputCommand(stringstream& ss);

void SYBD();

void InsertInto(string nameTable, string values);



#include "../Source/SYBD.cpp"

#endif