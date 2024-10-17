#include "../Headers/CSVSelect.h"


CSVSelect::CSVSelect(ReadingJSON& JSON) : JSON(JSON){}

void CSVSelect::SelectFromCSV(string& nameTable1,string& nameTable2,string& nameColumn1, string& nameColumn2)
{
    string pathToCSV1 = "../Source/" + JSON.GetNameMainDir()+"/" + nameTable1 + "/1.csv";
    string pathToCSV2 = "../Source/" + JSON.GetNameMainDir()+"/" + nameTable2 + "/1.csv";
    string pathToOutput = "../Source/" + JSON.GetNameMainDir()+"/" + nameTable1 + "_" + nameColumn1 + "_" + nameTable2 + "_" + nameColumn2 + "_cj.csv";

    ifstream inFile1(pathToCSV1);
    ifstream inFile2(pathToCSV2);
    ofstream outFile(pathToOutput);

    if (!inFile1.is_open()) 
    {
        cerr << "Ошибка открытия файла " << pathToCSV1 << endl;
        return;
    }
    if (!inFile2.is_open()) 
    {
        cerr << "Ошибка открытия файла " << pathToCSV2 << endl;
        return;
    }
    if (!outFile.is_open()) 
    {
        cerr << "Ошибка открытия файла " << pathToOutput << endl;
        return;
    }

    string header1, header2;
    getline(inFile1, header1);
    getline(inFile2, header2);

   
    int columnIndex1 = -1, columnIndex2 = -1;

    stringstream ss1(header1);
    stringstream ss2(header2);
    string column;
    int index = 0;

    while (getline(ss1, column, ',')) 
    {
        if (column == nameColumn1) 
        {
            columnIndex1 = index;
        }
        index++;
    }

    index = 0;
    while (getline(ss2, column, ',')) 
    {
        if (column == nameColumn2) 
        {
            columnIndex2 = index;
        }
        index++;
    }

   
    if (columnIndex1 == -1 || columnIndex2 == -1) 
    {
        cerr << "Одна или обе колонки не найдены." << endl;
        return;
    }

 
    outFile << nameColumn1 << "," << nameColumn2 << endl;

    
    LinkedList <string> valuesFromTable1;
    string line;

    while (getline(inFile1, line)) 
    {
        stringstream lineStream(line);
        string cell;
        int currentIndex = 0;

        while (getline(lineStream, cell, ',')) 
        {
            if (currentIndex == columnIndex1) 
            {
                valuesFromTable1.push_back(cell);
            }
            currentIndex++;
        }
    }

    LinkedList<string> valuesFromTable2;
    while (getline(inFile2, line)) 
    {
        stringstream lineStream(line);
        string cell;
        int currentIndex = 0;

        while (getline(lineStream, cell, ',')) 
        {
            if (currentIndex == columnIndex2) 
            {
                valuesFromTable2.push_back(cell);
            }
            currentIndex++;
        }
    }

    
    for (int i =0; i < valuesFromTable1.getSize(); i++) 
    {
        for (int j =0; j < valuesFromTable2.getSize(); j++) 
        {
            outFile << valuesFromTable1[i] << "," << valuesFromTable2[j] << endl;
        }
    }

    inFile1.close();
    inFile2.close();
    outFile.close();
}


bool CSVSelect::ParseCommandForSelect(LinkedList<string> nameTableFromQuery, LinkedList<string> nameColumnFromQuery, stringstream& stream)
{
    stream.ignore(1);
    string lineBeforCommandFROM;
    getline(stream, lineBeforCommandFROM,'F');

    regex pattern(R"((\w+)\.(\w+))"); 
    smatch matches;

    string text = lineBeforCommandFROM;

    auto it = text.cbegin();
    while (regex_search(it, text.cend(), matches, pattern))// заполнение листов с именами таблиц колонок
    {
        nameTableFromQuery.push_back(matches[1].str());  
        nameColumnFromQuery.push_back(matches[2].str());
       
        it = matches[0].second;               
    }

    for(int i = 0; i < nameTableFromQuery.getSize(); i++)// проверка на валидность введеных таблиц и колонок
    {
        if(JSON.IsValidTable(nameTableFromQuery[i]) == false)
        {
            cerr << "Ошибка. Неизвестная таблица " << nameTableFromQuery[i] << endl;
            return false;
        }
        if(JSON.IsValidColumns(nameTableFromQuery[i], nameColumnFromQuery[i]) == false)
        {
            cerr<<"Ошибка. Для данной таблицы " <<nameTableFromQuery[i]<<" нет такой колонки " <<nameColumnFromQuery[i]<<endl;
            return false;
        }
    
    }   

    string action;

    stream >> action;

    if(action != "FROM")
    {
        cerr<<"Ожидалась команда FROM, получена "<< action<<endl;
    }

    if(ParsePostQuery(nameTableFromQuery,stream) == false) return false;
    return true;
}


bool CSVSelect::ParsePostQuery(LinkedList<string> nameTableFromQuery, stringstream& stream)
{
    LinkedList <string> nameTablePostQuery;
    string nameTableAfterFROM;

    while(getline(stream,nameTableAfterFROM,' ') || getline(stream,nameTableAfterFROM,'W'))
    {
        nameTablePostQuery.push_back(nameTableAfterFROM);
    }

    int isValidTableInOrder = 0; // счетчик для проверки совпадания таблиц после FROM

    for(int i = 0; i < nameTableFromQuery.getSize(); i++)
    {
        if(nameTableFromQuery[i] == nameTablePostQuery[i]) isValidTableInOrder++;
    }  
    if(isValidTableInOrder == nameTableFromQuery.getSize()) return true;
    
    return false;
}