#include "../Headers/WorkWithFiles.h"

template <typename T>

Queue<T> extractDataFromQuery(string input) 
{
    Queue <string> queue;
    size_t start = 0, end = 0;

    // Найти первую открывающую скобку
    if (input.front() != '(' || input.back() != ')') {
        throw std::invalid_argument("Input must start with '(' and end with ')'");
    }

    // Пропустить первую и последнюю скобки
    start = 1;
    end = input.find("'", start);

    while (end != std::string::npos) {
        size_t nextEnd = input.find("'", end + 1);
        if (nextEnd == std::string::npos) break; // Если нет закрывающей кавычки

        // Извлечь значение между кавычками
        queue.push_front(input.substr(end + 1, nextEnd - end - 1));
        // Обновить start для поиска следующего значения
        end = input.find(",", nextEnd + 1);
        if (end == std::string::npos) break; // Если нет запятой, выходим из цикла
        start = end + 1; // Пропускаем запятую
        end = input.find("'", start);
    }

    
    return queue;
}



void InsertToCSV(string data, string pathToCSV)
{
    Queue<string> queueCSV = extractDataFromQuery<string>(data);

    string ff = "../Source/Схема 1";
    string fff = "1.csv";

    fs::path f1 = ff;
    fs::path f2 = fff;
    fs::path CSVFile = f1/pathToCSV/f2;

    ofstream outFile(CSVFile, ios::app);

    if (outFile.is_open()) 
    {
       while(queueCSV.getSize() != 0)
       {
            outFile <<"\n" << " ";
            for(int i = 0; i < 4; i++)
            {
            outFile << queueCSV.getFront()<<",";
            queueCSV.pop_back();
            }
            

       }
        outFile.close();
        
    } 
    else
    {
        cerr<<"File is not open"<<endl;

    }


}