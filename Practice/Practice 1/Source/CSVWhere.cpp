#include "../Headers/CSVWhere.h"

CSVWhere::CSVWhere(ReadingJSON& JSON) : JSON(JSON) {}

int CSVWhere::findColumnIndex(const string& header, const string& columnName) 
{
    stringstream ss(header);
    string column;

    int index = 0;

    while (getline(ss, column, ',')) 
    {
        if (column == columnName) 
        {
            return index;
        }
        index++;
    }
    return -1; // Колонка не найдена
}

bool CSVWhere::FunParseConditionNotValues(const string& condition, ParseConditionNotValue& parsed) 
{
    regex pattern(R"((\w+)\.(\w+)\s*=\s*(\w+)\.(\w+))");
    smatch matches;

    if (regex_match(condition, matches, pattern)) 
    {
        parsed.leftTable = matches[1];   
        parsed.leftColumn = matches[2];   
        parsed.rightTable = matches[3];  
        parsed.rightColumn = matches[4];  
        return true; 
    }
    return false; 
}

void CSVWhere::FunParseConditionValues(const string& condition, ParseConditionValue& parsed) 
{
    
    regex pattern(R"((\w+)\.(\w+)\s*=\s*'([^']+)')");
    smatch matches;


    if (regex_match(condition, matches, pattern)) 
    {
        parsed.table = matches[1];   
        parsed.column = matches[2];   
        parsed.value = matches[3];    
    }
}


void CSVWhere::StartWhere(LinkedList<string>&  nameTableFromQuery, 
                            LinkedList<string>& nameColumnFromQuery,
                            stringstream& stream)
{   
    string action;
    getline(stream, action);
    
    if(IsValidCondition(action)==false)// провека всей строки where
    {
        cerr<<"Строка после Where не прошла валидность"<<endl;
        return;
    }
    ParseWhereQuery(action);//парсинг условий и лог операции после where
    if(IsValidCommandPostWhere(nameTableFromQuery,nameColumnFromQuery)== false)//проверка таблица колонок после where с select
    {

        cerr<<"Несоответствие колонок или таблиц c SELECT FROM после WHERE"<<endl;
        return;
    }
    else
    {
        Filtration(nameTableFromQuery, nameColumnFromQuery);
    }
}

void CSVWhere::Filtration(LinkedList<string>&  nameTableFromQuery, LinkedList<string>& nameColumnFromQuery)
{
    ParseConditionNotValue parseNotValue;
    ParseConditionValue parseWithValue;

    string nameDirForFiltration =  "Filtration";
    try 
    {
        fs::create_directory(nameDirForFiltration);
    }
    catch (const fs::filesystem_error& e) 
    {
        cerr << "Ошибка создания: " << nameDirForFiltration << e.what() << '\n';
    }

    string pathToFinishFiltrationFile = "../Source/"+nameDirForFiltration+"/" + "1filt.csv";
    
    ofstream fileOutput(pathToFinishFiltrationFile);
    if(!(fileOutput.is_open()))
    {
        cout << pathToFinishFiltrationFile<<endl;
        cerr<<"File is not open";
    }
        for(int i = 0; i < operators.getSize(); i++)
        {
            if(operators[i] == "AND")
            {


            }
            if(operators[i] == "OR")
            {
                


            }


        }
        if(operators.getSize() == 0)
        {
            for(int i = 0; i < conditions.getSize(); i++)
            {
                if(FunParseConditionNotValues(conditions[i], parseNotValue)==true)
                {   
                    

                }
                else
                {
                    FunParseConditionValues(conditions[i], parseWithValue);

                    string pathToCSV = "../Source/"+JSON.GetNameMainDir()+"/"+ parseWithValue.table+"/1.csv";
                    string line;
                    ifstream inFile(pathToCSV);
                    getline(inFile, line);
                    int indexColumn = 0;

                    indexColumn = findColumnIndex(line, parseWithValue.column);

                    while (getline(inFile, line)) 
                    {
                        stringstream lineStream(line);
                        string cell;
                        int currentIndex = 0;

                        while (getline(lineStream, cell, ',')) 
                        {
                            if (currentIndex == indexColumn && cell == parseWithValue.value) 
                            {
                               fileOutput<<line<<"\n";
                            }
                            currentIndex++;
                        }
                    }

                }
            }


        }

    fileOutput.close();

}




bool CSVWhere::IsValidCommandPostWhere(LinkedList<string>&  nameTableFromQuery, LinkedList<string>& nameColumnFromQuery) 
{
    string nameTableAfterWhere, nameColumnAfterWhere;
    regex pattern(R"((\w+)\.(\w+))"); 
    smatch matches;

    for(int i = 0; i < conditions.getSize(); i++)
    {
        string text = conditions[i];
        auto it = text.cbegin();
        while (regex_search(it, text.cend(), matches, pattern)) 
        {
            nameTableAfterWhere = matches[1].str();  
            nameColumnAfterWhere = matches[2].str();
            if(nameTableFromQuery.search_by_value(nameTableAfterWhere) == false) return false;
            if(nameColumnFromQuery.search_by_value(nameColumnAfterWhere) == false) return false;
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
        conditions.push_back(match[0]);// имена таблица после where 
        searchStart = match.suffix().first; // имена колонок после where
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
        cerr<<"Неверный формат "<<endl;
        return false; // Неверный формат
    }

    // Проверяем, что AND и OR не стоят рядом
   string modifiedCondition =regex_replace(condition,regex(R"(\s+(AND|OR)\s+)"), " $1 ");
    
    if (modifiedCondition.find(" AND AND ") !=string::npos || modifiedCondition.find(" OR OR ") !=string::npos)
    {
        cerr<<"OR либо AND стоят рядом "<<endl;
        return false;
    }

    // Проверяем, что AND имеет условия с обеих сторон
    size_t andPos = modifiedCondition.find(" AND ");
    while (andPos !=string::npos) 
    {
        if (andPos == 0 || andPos + 5 >= modifiedCondition.length() || modifiedCondition[andPos + 5] == ' ') 
        {
            cerr<<"AND не закрыто условиями " <<endl;
            return false; // AND не обрамлено условиями
        }
        andPos = modifiedCondition.find(" AND ", andPos + 5);
    }

    return true; 
}