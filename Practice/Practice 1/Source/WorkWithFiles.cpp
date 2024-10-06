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
        queue.push_back(input.substr(end + 1, nextEnd - end - 1));
        // Обновить start для поиска следующего значения
        end = input.find(",", nextEnd + 1);
        if (end == std::string::npos) break; // Если нет запятой, выходим из цикла
        start = end + 1; // Пропускаем запятую
        end = input.find("'", start);
    }

    
    return queue;
}



void InsertToCSV(string data, string nameTable)
{
    Queue<string> queueCSV = extractDataFromQuery<string>(data);

    string firstPartPathToCSV = "../Source/Схема 1";
    string secondPartPathToCSVf = "1.csv";

    fs::path firstPart = firstPartPathToCSV;
    fs::path secondPart = secondPartPathToCSVf;

    fs::path CSVFile = firstPart/nameTable/secondPart;

    ofstream outFile(CSVFile, ios::app);

    if (outFile.is_open()) 
    {
        if(nameTable == "Таблица1")
        {
            while(queueCSV.getSize() != 0)
            {
                outFile <<"\n" << " "<<",";
                for(int i = 0; i < 4; i++)
                {
                outFile << queueCSV.getFront()<<",";
                WorkWithFile_pk_sequence(nameTable);
                queueCSV.pop_front();
                if(queueCSV.getSize() == 0) return;
                }
            }

        }
      
        if(nameTable == "Таблица2")
        {
            while(queueCSV.getSize() != 0)
            {
                outFile <<"\n" << " "<<",";
                for(int i = 0; i < 2; i++)
                {
                outFile << queueCSV.getFront()<<",";
                WorkWithFile_pk_sequence(nameTable);
                queueCSV.pop_front();
                if(queueCSV.getSize() == 0) return;
                }


            }

        }
        outFile.close();
        
    } 
    else
    {
        cerr<<"File"<< CSVFile <<"is not open"<<endl;

    }

}

void WorkWithFile_pk_sequence(fs::path nameTable)
{
    string firstPartPath = "../Source/Схема 1";
    string pk_sequence = "pk_sequence.txt";
    
    fs::path nameFile = firstPartPath / nameTable / pk_sequence;

    // Проверяем, существует ли файл
    ifstream inFile(nameFile);

    int lineCount = 0;
    
    // Если файл существует, подсчитываем строки
    if (inFile.is_open()) 
    {
        string line;
        while (getline(inFile, line)) 
        {
            lineCount++;
        }
        inFile.close(); 
    }
    else 
    {
        // Если файл не существует, создаем его
        ofstream outFile(nameFile);
        if (outFile.is_open()) 
        {
            outFile << 0; // Записываем 0, если файла не было
            outFile.close();
            cerr << "Файл создан: " << nameFile << endl;
        }
        else 
        {
            cerr << "Не удалось создать файл " << nameFile << endl;
            return;
        }
    }

    // Открываем файл для записи количества строк
    ofstream outFile(nameFile);
    if (outFile.is_open()) 
    {
        outFile << lineCount; // Записываем количество строк
        outFile.close();
    } 
    else
    {
        cerr << "Файл " << nameFile << " не открыт для записи" << endl;
    }
}