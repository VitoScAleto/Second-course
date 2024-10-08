#include "../Headers/WorkWithFiles.h"

template <typename T>

Queue<T> extractDataFromQuery(string input) 
{
    Queue <string> queue;
    size_t start = 0, end = 0;

    // Найти первую открывающую скобку
    if (input.front() != '(' || input.back() != ')') 
    {
        throw invalid_argument("Input must start with '(' and end with ')'");
    }

    // Пропустить первую и последнюю скобки
    start = 1;
    end = input.find("'", start);

    while (end != string::npos) 
    {
        size_t nextEnd = input.find("'", end + 1);
        if (nextEnd == string::npos) break; // Если нет закрывающей кавычки

        // Извлечь значение между кавычками
        queue.push_back(input.substr(end + 1, nextEnd - end - 1));
        // Обновить start для поиска следующего значения
        end = input.find(",", nextEnd + 1);
        if (end == string::npos) break; // Если нет запятой, выходим из цикла
        start = end + 1; // Пропускаем запятую
        end = input.find("'", start);
    }

    
    return queue;
}


void WorkWithCSV(string data, string nameTable)
{
    CSV csv;
    csv.WriteToCSV(data, nameTable);


}


void CSV::WriteToCSV(string data, string nameTable)
{
    Queue <string> queueQuery = extractDataFromQuery<string>(data);

    if(nameTable == "Таблица1")
    {
        string pathToCSV = "../Source/Схема 1/" + nameTable + "/1.csv";

        ofstream outFile(pathToCSV, ios::app);
        
        if(!outFile.is_open())
        {
        cerr << "Error: Could not open the file " << pathToCSV << endl;
        throw ios_base::failure("Failed to open file: " + pathToCSV);
        }

        while(queueQuery.getSize() != 0)
        {    
            outFile.close();
            ofstream outFile(pathToCSV, ios::app);

            int quantityElementInCSVFileT1 = CountElementInCSV(nameTable);

            quantityElementInCSVFileT1 %= 5;

            if(quantityElementInCSVFileT1 == 0)
            {
                outFile<<"\n"<<WorkWithFile_pk_sequence(nameTable)<<",";
                quantityElementInCSVFileT1++;
            }
            for(int i = 0; i < 5 - quantityElementInCSVFileT1 && queueQuery.getSize() != 0; i++)
            {
                outFile << queueQuery.getFront()<<",";
                queueQuery.pop_front();
                
            }

        }

        outFile.close();
        return;
    }
    
    if(nameTable == "Таблица2")
    {

        string pathToCSV = "../Source/Схема 1/" + nameTable + "/1.csv";

        ofstream outFile(pathToCSV, ios::app);
        if(!outFile.is_open())
        {
        cerr << "Error: Could not open the file " << pathToCSV << endl;
        throw ios_base::failure("Failed to open file: " + pathToCSV);
        }

        while(queueQuery.getSize() != 0)
        {   
            outFile.close();// для обновления файла
            ofstream outFile(pathToCSV, ios::app);// для обновления файла

            int quantityElementInCSVFileT2 = CountElementInCSV(nameTable);

            quantityElementInCSVFileT2 %= 3;

            if(quantityElementInCSVFileT2 == 0)
            {
               outFile<<"\n"<<WorkWithFile_pk_sequence(nameTable)<<",";
               quantityElementInCSVFileT2++;
            }
            
            for(int i = 0; i < 3 - quantityElementInCSVFileT2 && queueQuery.getSize() != 0; i++)
            {
               
                outFile << queueQuery.getFront()<<",";
                queueQuery.pop_front();
            }
            quantityElementInCSVFileT2 = 0;

        }
      

        outFile.close();
        return;
    }
    throw invalid_argument("Invalid table name: " + nameTable);



}

int CSV::CountElementInCSV(string nameTable)
{
    numberColumns = 0;
    if(nameTable == "Таблица1")
    {
        string pathToCSV = "../Source/Схема 1/" + nameTable + "/1.csv";

        ifstream outFile(pathToCSV);
        
        if(!outFile.is_open())
        {
        cerr << "Error: Could not open the file " << pathToCSV << endl;
        throw ios_base::failure("Failed to open file: " + pathToCSV);
        }

        string line;

        while (std::getline(outFile, line)) 
        {
           stringstream ss(line);
           string item;

            while (std::getline(ss, item, ',')) 
            {
                numberColumns++;
            }

        }
        outFile.close();
        return numberColumns;
    }
    
    if(nameTable == "Таблица2")
    {
        string pathToCSV = "../Source/Схема 1/" + nameTable + "/1.csv";

       
        ifstream outFile(pathToCSV);
        if(!outFile.is_open())
        {
        cerr << "Error: Could not open the file " << pathToCSV << endl;
        throw ios_base::failure("Failed to open file: " + pathToCSV);
        }


        string line;

        while (std::getline(outFile, line)) 
        {
           stringstream ss(line);
           string item;

            while (std::getline(ss, item, ',')) 
            {
                numberColumns++;
            }

        }

        outFile.close();
        return numberColumns;
    }
    throw invalid_argument("Invalid table name: " + nameTable);


}

CSV::CSV()
{
    numberColumns = 0;

}




int CSV::WorkWithFile_pk_sequence(string nameTable)
{
    string pkFilePath = "../Source/Схема 1/" + nameTable + "/" + nameTable + "_pk_sequence.txt";

    int currentPk = 0;

    ifstream pkFile(pkFilePath);

    if (pkFile.is_open()) 
    {
        pkFile >> currentPk; 
        pkFile.close();
    } 
    else 
    {
        ofstream createFile(pkFilePath);
        if (createFile.is_open()) 
        {
            createFile << currentPk; // Записываем начальное значение
            createFile.close();
        }
        else 
        {
             throw ios_base::failure("Failed to сreate file: " + pkFilePath);
        }
    }

    currentPk++;

    ofstream outPkFile(pkFilePath);
    if (outPkFile.is_open()) 
    {
        outPkFile << currentPk; 
        outPkFile.close();
    } 
    else 
    {
        cerr << "File " << pkFilePath << " is not open for writing." << endl;
    }
    return currentPk;
}


