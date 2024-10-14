#include "../Headers/CSVWhere.h"

CSVWhere::CSVWhere(ReadingJSON& JSON) : JSON(JSON) {}

void CSVWhere::StartWhere(string& nameTable1,string& nameTable2,string& nameColumn1, string& nameColumn2,stringstream& stream)
{
    string action;
    getline(stream,action);

    if(IsValidCondition(action)==false)
    {
        cerr<<"Строка после Where не прошла валидность"<<endl;
        return;
    }
    ParseWhereQuery(stream);
    if(IsValidCommandPostWhere(nameTable1,nameTable2,nameColumn1, nameColumn2)== false)
    {

        cerr<<"Несоответствие колонок или таблиц c SELECT FROM после WHERE"<<endl;
        return;
    }
}

bool CSVWhere::IsValidCommandPostWhere(string nameTable1, string nameTable2, string nameColumn1, string nameColumn2) 
{
    string nameTableAfterWhere, nameColumnAfterWhere;
    stringstream s1;

    for (int i = 0; i < conditions.getSize(); i++) {
        s1.str(conditions[i]);  // Устанавливаем строку для разбора
        s1.clear();  // Очищаем флаги состояния

        // Извлекаем таблицу и колонку
        getline(s1, nameTableAfterWhere, '.');
        if (nameTableAfterWhere != nameTable1 || nameTableAfterWhere != nameTable2) 
        {
            cerr << "Неизвестная таблица Функция(IsValidCommandPostWhere) Ожидалась таблица " 
                 << nameTable1 << " либо " << nameTable2 << " получена " << nameTableAfterWhere << endl;
            return false;
        }

        // Извлекаем колонку
        getline(s1, nameColumnAfterWhere, ' ');

        // Проверяем наличие колонки в схеме
        Queue<string> queueColumns = JSON.GetColumnsFromSchema<string>(nameTableAfterWhere);
        bool columnExists = false;
        while (queueColumns.getSize() != 0) {
            if (nameColumnAfterWhere == queueColumns.getFront()) {
                columnExists = true;
                break;
            }
            queueColumns.pop_front();
        }

        if (!columnExists) {
            cerr << "Такой колонки нет " << nameColumnAfterWhere << endl;
            return false;
        }

        // Пропускаем оставшуюся часть условия
        string temp;
        getline(s1, temp);  // Читаем оставшуюся часть строки
    }

    return true;
}



void CSVWhere::ParseWhereQuery(stringstream& stream)
{
    string whereClause;
    stream.ignore(1);
    getline(stream, whereClause);
   
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
    
    if (!std::regex_match(condition, conditionRegex)) 
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