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
        Filtration();
    }
}

void CSVWhere::Filtration()
{
    ParseConditionNotValue parseNotValue;
    ParseConditionValue parseWithValue;
    LinkedList<string> first;
    LinkedList<string> second;
    LinkedList<string> tri;
    LinkedList<string> chert;

    string nameDirForFiltration =  JSON.GetNameMainDir()+"/Filtration";
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
    while(ss.search_by_value_bool("AND")==true)
    {
        int indexAND = ss.search_by_value_return_index("AND");

        ss.delete_by_index(indexAND);

        indexAND--;

        for(int i = 0; i < 2; i++)
        {
            indexAND += i;
            if(FunParseConditionNotValues(ss[indexAND], parseNotValue) == true)
            {
                string pathFileToRead1 = "../Source/"+JSON.GetNameMainDir()+"/"+parseNotValue.leftTable+"/1.csv";
                string pathFileToRead2 = "../Source/"+JSON.GetNameMainDir()+"/"+parseNotValue.rightTable+"/1.csv";

                ifstream inFile1(pathFileToRead1);
                ifstream inFile2(pathFileToRead2);

                string header1, header2;

                getline(inFile1, header1);
                int columnIndex1 = findColumnIndex(header1, parseNotValue.leftColumn);

                getline(inFile2, header2);
                int columnIndex2 = findColumnIndex(header2, parseNotValue.rightColumn);

                first.push_back(header1);
                second.push_back(header2);
                

                while(getline(inFile1, header1) && getline(inFile2, header2))
                {
                    stringstream lineStream1(header1);
                    string cell1;
                    int currentIndex1 = 0;

                    while (getline(lineStream1, cell1, ',')) 
                    {
                        if (currentIndex1 == columnIndex1) 
                        {
                            break;
                        }
                        currentIndex1++;
                    }
                    stringstream lineStream2(header2);
                    string cell2;
                    int currentIndex2 = 0;

                    while (getline(lineStream2, cell2, ',')) 
                    {
                        if (currentIndex2 == columnIndex2) 
                        {
                            break;
                        }
                        currentIndex2++;
                    }
                    if(cell1 == cell2)
                    {
                        first.push_back(header1);
                        second.push_back(header2);
                    }

                }
                for(int i  = 0; i < first.getSize();i++)
                {
                    fileOutput<<first[i]<<"\t"<<second[i]<<"\n";
                }
               
                first.~LinkedList();
                second.~LinkedList();
               
            }
            else
            {
                FunParseConditionValues(ss[indexAND], parseWithValue);


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
            if(nameTableFromQuery.search_by_value_bool(nameTableAfterWhere) == false) return false;
            if(nameColumnFromQuery.search_by_value_bool(nameColumnAfterWhere) == false) return false;
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

    
    
    auto conditionBegin = sregex_iterator(whereClause.begin(), whereClause.end(), conditionPattern);
    auto conditionEnd = sregex_iterator();
    
    auto operatorBegin = sregex_iterator(whereClause.begin(), whereClause.end(), operatorPattern);
    auto operatorEnd = sregex_iterator();
    
    // Добавляем условия и операторы поочередно
    auto condIt = conditionBegin;
    auto opIt = operatorBegin;

    while (condIt != conditionEnd || opIt != operatorEnd) {
        if (condIt != conditionEnd) {
            ss.push_back(condIt->str());
            ++condIt;
        }
        if (opIt != operatorEnd) {
            ss.push_back(opIt->str());
            ++opIt;
        }
    }
   
}



bool CSVWhere::IsValidCondition(string condition) 
{
   
    regex conditionRegex(R"(\s*(\w+\.\w+\s*=\s*('[^']*'|\w+\.\w+))(\s+(AND|OR)\s+(\w+\.\w+\s*=\s*('[^']*'|\w+\.\w+)))*\s*$)");
    
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