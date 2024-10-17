#include "../Headers/CSVWhere.h"

CSVWhere::CSVWhere(ReadingJSON& JSON) : JSON(JSON) {}

void CSVWhere::StartWhere(string& nameTable1,string& nameTable2,string& nameColumn1, string& nameColumn2,stringstream& stream)
{   
    string action;
    getline(stream, action);
    
    if(IsValidCondition(action)==false)
    {
        cerr<<"Строка после Where не прошла валидность"<<endl;
        return;
    }
    ParseWhereQuery(action);
    if(IsValidCommandPostWhere(nameTable1,nameTable2,nameColumn1, nameColumn2)== false)
    {

        cerr<<"Несоответствие колонок или таблиц c SELECT FROM после WHERE"<<endl;
        return;
    }
    else
    {
        cout<<"All good"<<endl;
    }
}

bool CSVWhere::IsValidCommandPostWhere(string nameTable1, string nameTable2, string nameColumn1, string nameColumn2) 
{
    string nameTableAfterWhere, nameColumnAfterWhere;
    regex pattern(R"((\w+)\.(\w+))"); 
    smatch matches;

    LinkedList<string> tables;  
    LinkedList<string> columns;   

    for(int i =0; i < conditions.getSize(); i++)
    {
        string text = conditions[i];
        auto it = text.cbegin();
        while (regex_search(it, text.cend(), matches, pattern)) 
        {
            nameTableAfterWhere = matches[1].str();  
            if(nameTableAfterWhere != nameTable1 || nameTableAfterWhere != nameTable2) return false;
            nameColumnAfterWhere = matches[2].str();
            if(nameColumnAfterWhere != nameColumn1 || nameColumnAfterWhere != nameColumn2) return false;
            it = matches[0].second;               
        }
    }
    return true;
}



void CSVWhere::ParseWhereQuery(string whereClause)
{
   
    smatch match;
    regex conditionPattern(R"((\w+\.\w+)\s*=\s*(\w+\.\w+)|(\w+\.\w+)\s*=\s*'([^']+)')");

    string::const_iterator searchStart(whereClause.cbegin());
    while (regex_search(searchStart, whereClause.cend(), match, conditionPattern)) 
    {
        conditions.push_back(match[0]);
        searchStart = match.suffix().first; 
    }
  
    regex operatorPattern(R"(\b(AND|OR)\b)");

    sregex_token_iterator iter(whereClause.begin(), whereClause.end(), operatorPattern, 0);
    sregex_token_iterator end;

    while (iter != end) 
    {
        operators.push_back(*iter++);
    }
}

bool CSVWhere::IsValidCondition(string condition) 
{
   

    regex conditionRegex(R"(\s*(\w+\.\w+\s*=\s*('[^']*'|\w+\.\w+))(\s+(AND|OR)\s+(\w+\.\w+\s*=\s*('[^']*'|\w+\.\w+)))*$)");
    
    if (!regex_match(condition, conditionRegex)) 
    {
        return false; // Неверный формат
    }

    // Проверяем, что AND и OR не стоят рядом
   string modifiedCondition =regex_replace(condition,regex(R"(\s+(AND|OR)\s+)"), " $1 ");
    
    if (modifiedCondition.find(" AND AND ") !=string::npos || modifiedCondition.find(" OR OR ") !=string::npos)
    {
        return false; // AND или OR стоят рядом
    }

    // Проверяем, что AND имеет условия с обеих сторон
    size_t andPos = modifiedCondition.find(" AND ");
    while (andPos !=string::npos) 
    {
        if (andPos == 0 || andPos + 5 >= modifiedCondition.length() || modifiedCondition[andPos + 5] == ' ') 
        {
            return false; // AND не обрамлено условиями
        }
        andPos = modifiedCondition.find(" AND ", andPos + 5);
    }

    return true; 
}