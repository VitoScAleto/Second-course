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


bool CSVSelect::ParseCommandForSelect(string& nameTable1,string& nameTable2,string& nameColumn1, string& nameColumn2, stringstream& stream)
{
    stream.ignore(1);
    getline(stream,nameTable1,'.');
    getline(stream,nameColumn1,' ');
    getline(stream,nameTable2,'.');
    getline(stream,nameColumn2,' ');

    if (JSON.IsValidTable(nameTable1) == false || JSON.IsValidTable(nameTable2)==false) 
    {
        cerr << "Unknown table.(Function -> ParseCommandForSelect())" << endl;
        throw invalid_argument("This table not found");
    }
    Queue<string> queueColumns1 = JSON.GetColumnsFromSchema<string>(nameTable1);

    Queue<string> queueColumns2 = JSON.GetColumnsFromSchema<string>(nameTable2);

    while(queueColumns1.getSize()!=0)
    {
        if(nameColumn1 == queueColumns1.getFront()) break;
        queueColumns1.pop_front();
        if(queueColumns1.getSize() == 0)
        {
            cerr<<"Такой колонки нет"<<nameColumn1<<endl;
            return false;
        }
    }
    while(queueColumns2.getSize()!=0)
    {
        if(nameColumn2 == queueColumns2.getFront()) break;
        queueColumns2.pop_front();
        if(queueColumns2.getSize() == 0)
        {
            cerr<<"Такой колонки нет"<<nameColumn2<<endl;
            return false;
        }
    }
    
    string action;

    stream >> action;

    if(action != "FROM")
    {
        cerr<<"Ожидалась команда FROM, получена "<< action<<endl;
    }

    if(ParsePostQuery(nameTable1, nameTable2,stream) == false) return false;
    return true;
}


bool CSVSelect::ParsePostQuery(const string nameTable1, const string nameTable2, stringstream& stream)
{
    string nameTableAfterFROM1, nameTableAfterFROM2;

    stream >> nameTableAfterFROM1;
    stream >> nameTableAfterFROM2;

    if(nameTableAfterFROM1 != nameTable1 || nameTableAfterFROM2 != nameTable2)
    {
        
        return false;

    }
    return true;
}