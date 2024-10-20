#include "../Headers/CSVDelete.h"

CSVDelete::CSVDelete(ReadingJSON& JSON) : JSON(JSON){}



void CSVDelete::DeleteStart(stringstream& stream)
{
    string nameTable, nameColumn, equalSym, value;

    ParseCommandForDelete(nameTable, nameColumn, equalSym, value, stream);

    DeleteFromCSV(nameTable, nameColumn, value);

}


void CSVDelete::ParseCommandForDelete(string& nameTable, string& nameColumn, string& equalSym, string& value, stringstream& stream)
{
    stream.ignore(1);
    getline(stream, nameTable, '.');
    

    if (JSON.IsValidTable(nameTable) == false) 
    {
        cerr << "Unknown table.(Function -> ParseCommandForDelete())" << endl;
        return;
    }
    getline(stream, nameColumn, ' ');

    if(JSON.IsValidColumns(nameTable, nameColumn) == false)
    {
        cerr<<"Ошибка. Для данной таблицы "<<nameTable<<" нет такой колоник "<<nameColumn<<endl;
        return;
    }

    getline(stream, equalSym, ' '); 

    if(equalSym != "=")
    {
        cerr<<"This is"<<equalSym << " not ="<<endl;
        return;
    }

    string temp;
    getline(stream, temp, '\'');
    getline(stream, value, '\'');
}

void CSVDelete::DeleteFromCSV(string nameTable, string nameColumn, string valuesToDelete)
{

    if(JSON.IsValidTable(nameTable) == false)
    {
        cerr<<"Неизветная таблица " << nameTable<<endl;
        return;
    }
    string pathToCSV = "../Source/" + JSON.GetNameMainDir()+"/"+ nameTable + "/1.csv";

    ifstream inFile(pathToCSV);
    ofstream outFile("temp.csv"); // Временный файл для записи отфильтрованных данных

    if (!inFile.is_open() ) 
    {
        cerr << "Ошибка открытия файла inFile!(Function -> DeleteFromCSV" << endl;
        return;
    }
    if(!outFile.is_open())
    {
        cerr << "Ошибка открытия файла outFile!(Function -> DeleteFromCSV" << endl;
        return;
    }
    string line;
    getline(inFile, line);
    outFile << line << endl; 

    // Получаем индекс колонки
    stringstream ss(line);
    string column;
    LinkedList <string> headers;

    int columnIndex = -1;
    int index = 0;

    while (getline(ss, column, ',')) 
    {
        headers.push_back(column);
        if (column == nameColumn) 
        {
            columnIndex = index; // Запоминаем индекс колонки
        }
        index++;
    }

 
    while (getline(inFile, line)) 
    {
        stringstream lineStream(line);
        string cell;
        LinkedList <string> row;
       

        while (getline(lineStream, cell, ',')) 
        {
            row.push_back(cell);
        }

        if (columnIndex != -1 && row.search_by_value_bool(valuesToDelete) == columnIndex) 
        {
            row.~LinkedList(); 
        }
       
        while(row.getSize()!=0)
        {
            // outFile.close();
            // ofstream outFile("temp.csv", ios::app);
            outFile<<row.getHead()<<",";
            row.pop_front();
        }
        if (!(columnIndex != -1 && row.search_by_value_bool(valuesToDelete) == columnIndex)) outFile<<endl;
    }
    inFile.close();
    outFile.close();

    // Заменяем оригинальный файл временным
    remove(pathToCSV.c_str());
    rename("temp.csv", pathToCSV.c_str());
}



// void CSVDelete::DeleteFromCSV(string nameTable, string nameColumn, string valuesToDelete)
// {
//     string pathToCSV;

//     if(nameTable == JSON.GetNameTable1JSON())
//     {
//         pathToCSV = JSON.GetPathToTable1JSON()+"/1.csv";
//     }
//     else
//     {
//         pathToCSV = JSON.GetPathToTable2JSON()+"/1.csv";
//     }

//     ifstream inFile(pathToCSV);
//     ofstream outFile("temp.csv"); // Временный файл для записи отфильтрованных данных

//     if (!inFile.is_open() ) 
//     {
//         cerr << "Ошибка открытия файла inFile!(Function -> DeleteFromCSV" << endl;
//         return;
//     }
//     if(!outFile.is_open())
//     {
//         cerr << "Ошибка открытия файла outFile!(Function -> DeleteFromCSV" << endl;
//         return;
//     }
//     string line;
//     getline(inFile, line);
//     outFile << line << endl; 

//     // Получаем индекс колонки
//     stringstream ss(line);
//     string column;
//     LinkedList <string> headers;

//     int columnIndex = -1;
//     int index = 0;

//     while (getline(ss, column, ',')) 
//     {
//         headers.push_back(column);
//         if (column == nameColumn) 
//         {
//             columnIndex = index; // Запоминаем индекс колонки
//         }
//         index++;
//     }

 
//     while (getline(inFile, line)) 
//     {
//         stringstream lineStream(line);
//         string cell;
//         LinkedList <string> row;
       

//         while (getline(lineStream, cell, ',')) 
//         {
//             row.push_back(cell);
//         }

//         if (columnIndex != -1 && row.search_by_value(valuesToDelete) == columnIndex) 
//         {
//             row.Replace_by_index(columnIndex, " "); 
//         }

//         while(row.getSize()!=0)
//         {
//             outFile.close();
//             ofstream outFile("temp.csv", ios::app);
//             outFile<<row.getHead()<<",";
//             row.pop_front();
//         }
//         outFile<<"\n";
//     }

//     inFile.close();
//     outFile.close();

//     // Заменяем оригинальный файл временным
//     remove(pathToCSV.c_str());
//     rename("temp.csv", pathToCSV.c_str());
// }