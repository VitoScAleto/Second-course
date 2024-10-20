#include "../Headers/CSVSelect.h"

CSVSelect::CSVSelect(ReadingJSON& JSON) : JSON(JSON){}

int CSVSelect::findColumnIndex(const string& header, const string& columnName) 
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



void CSVSelect::SelectFromCSV(LinkedList<string>& nameTableFromQuery, LinkedList<string>& nameColumnFromQuery)
{
    
    LinkedList<string> listPathToCSV;

    for(int i = 0; i < nameTableFromQuery.getSize(); i++)
    {
        string pathToCSV = "../Source/"+JSON.GetNameMainDir() + "/"+ nameTableFromQuery[i]+"/1.csv";
        listPathToCSV.push_back(pathToCSV);
    }
    string pathToOutput = "../Source/" + JSON.GetNameMainDir() + "/" + nameTableFromQuery[0] + "-" + nameTableFromQuery[nameTableFromQuery.getSize()-1]+ nameColumnFromQuery[0] + "_cj.csv";

    ifstream inFile1(listPathToCSV[0]);
    if (!inFile1.is_open()) 
    {
        cerr << "Ошибка открытия файла " << listPathToCSV[0] << endl;
        return;
    }

    ifstream inFile2(listPathToCSV[1]);
    if (!inFile1.is_open()) 
    {
        cerr << "Ошибка открытия файла " << listPathToCSV[1] << endl;
        return;
    }
    
    string header;
    int columnIndex1 = -1, columnIndex2 = -1;

    getline(inFile1, header);
    columnIndex1 = findColumnIndex(header,nameColumnFromQuery[0]);
    getline(inFile2, header);
    columnIndex2 = findColumnIndex(header,nameColumnFromQuery[1]);
   
   
    ofstream intermediateFile(pathToOutput); 
    intermediateFile << nameTableFromQuery[0]<< nameColumnFromQuery[0]<<","<< nameTableFromQuery[1]<<nameColumnFromQuery[1] << ","<< endl;

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
    for (int i = 0; i < valuesFromTable1.getSize(); i++) 
    {
        for (int j =0; j < valuesFromTable2.getSize(); j++) 
        {
            intermediateFile << valuesFromTable1[i] << "," << valuesFromTable2[j] << endl;
        }
    }
    inFile1.close();
    inFile2.close();
    intermediateFile.close();

    valuesFromTable1.~LinkedList();
    valuesFromTable2.~LinkedList();
    
    for(int i = 2; i < listPathToCSV.getSize(); i++)
    {

        ifstream intermediateFile(pathToOutput);
        while(getline(intermediateFile, header))
        {
            valuesFromTable1.push_back(header);
        }
        intermediateFile.close();

        ifstream inFile(listPathToCSV[i]);
        if (!inFile.is_open()) 
        {
            cerr << "Ошибка открытия файла " << listPathToCSV[i] << endl;
            return;
        }
        
        getline(inFile, header);

        int columnIndex = findColumnIndex(header,nameColumnFromQuery[i]);

        string line;

        while (getline(inFile, line)) 
        {
            stringstream lineStream1(line);
            string cell2;
            int currentIndex = 0;

            while (getline(lineStream1, cell2, ',')) 
            {
                if (currentIndex == columnIndex) 
                {
                    valuesFromTable2.push_back(cell2);
                }
                currentIndex++;
            }
        }
        inFile.close();

        ofstream intermediateFile1(pathToOutput);
        intermediateFile1<<valuesFromTable1[0]<<nameTableFromQuery[i]<<nameColumnFromQuery[i]<<","<<endl;

        for (int i =1; i < valuesFromTable1.getSize(); i++) 
        {
            for (int j =0; j < valuesFromTable2.getSize(); j++) 
            {
                intermediateFile1 << valuesFromTable1[i] << "," << valuesFromTable2[j] << endl;
            }
        }
        valuesFromTable1.~LinkedList();
        valuesFromTable2.~LinkedList();
        intermediateFile1.close();


    }



}

bool CSVSelect::ParseCommandForSelect(LinkedList<string>& nameTableFromQuery, LinkedList<string>& nameColumnFromQuery, stringstream& stream)
{
    stream.ignore(1);
    string lineBeforCommandFROM;
    getline(stream, lineBeforCommandFROM,'F');
    stream.putback('F');
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

    if(IsValidAfterFROM(nameTableFromQuery,stream) == false) return false;
    return true;
}


bool CSVSelect::IsValidAfterFROM(LinkedList<string>& nameTableFromQuery, stringstream& stream)
{
    string whereClause;
    string nameTableAfterFROM;
    stream.ignore(1);

   while (stream >> nameTableAfterFROM) 
   { 
        if (nameTableAfterFROM == "WHERE") 
        {
            getline(stream, whereClause);
            whereClause = "WHERE" + whereClause;
            stream.clear();
            stream.str("");
            stream << whereClause;
            break;
        }

        if (!JSON.IsValidTable(nameTableAfterFROM)) 
        {
            std::cerr << "Ошибка. Неизвестная таблица " << nameTableAfterFROM << " после FROM " << std::endl;
            return false;
        }

        if(nameTableFromQuery.search_by_value_bool(nameTableAfterFROM) == false)
        {
            cerr<<"Данная таблица " << nameTableAfterFROM << " не указана в SELECT"<<endl;
            return false;

        }
    }

    return true;
}