#ifndef PARSE_QUERY_H
#define PARSE_QUERY_H

#include "../Headers/Array.h"
#include "../Headers/DLList.h"
#include "../Headers/ComBinTree.h"
#include "../Headers/queue.h"
#include "../Headers/stack.h"
#include "../Headers/FList.h"
#include <regex>


class  FieldQuery
{
    private:

    public:
    
    FieldQuery();

    char structureType;
    string index;
    string method;
    string name;
    string value;
    string filePath;
};

class ParseQuery
{
    private:

    public:

    void handleCommand(FieldQuery& fieldQuery);

    bool isValidCommand(const string& command);

    void parseCommand(const string& command);

};







#include "../Source/ParseQuery.cpp"


#endif 