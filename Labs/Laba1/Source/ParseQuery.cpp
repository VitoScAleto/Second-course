#include "../Headers/ParseQuery.h"

FieldQuery::FieldQuery(){}


void ParseQuery::handleCommand(FieldQuery& fieldQuery) 
{
    switch (fieldQuery.structureType) 
    {
        case 'T': 
        {
            if(fieldQuery.name != "mytree")
            {
                cerr<<"Ошибка. Такой структуры "<<fieldQuery.name<<" не существует"<<endl;
                return;
            }
            ComBinTree<string> tree;
            tree.readingConfiguration(fieldQuery.filePath);
            if (fieldQuery.method == "find") 
            {
                cout<< tree.find(fieldQuery.value)<<endl;
            } 
            else if (fieldQuery.method == "push") 
            {
                tree.push(fieldQuery.value);
            }
            else if (fieldQuery.method == "complete") 
            {
                cout<< tree.isComplete()<<endl;
            } 
            else if (fieldQuery.method == "print") 
            {
                tree.display();
            }
            tree.writeToConfiguration(fieldQuery.filePath);
            break;
        }
        case 'M': // Массив
        {
            if(fieldQuery.name != "myarray")
            {
                cerr<<"Ошибка. Такой структуры "<<fieldQuery.name<<" не существует"<<endl;
                return;
            }
    MyArray<string> array(5);
            array.readingConfiguration(fieldQuery.filePath);
            if (fieldQuery.method == "getSize") 
            {
                cout << "Size: " << array.getSize() << endl;
            }
            else if (fieldQuery.method == "get_by_index") 
            {
                stringstream ss(fieldQuery.value);
                int num;
                ss >> num;
                cout<< array[num]<<endl;
            } 
            else if (fieldQuery.method == "push_back") 
            {
                array.push_back(fieldQuery.value);
            }
            else if (fieldQuery.method == "insert_by_index") 
            {
                stringstream ss(fieldQuery.index);
                int num;
                ss >> num;
                array.insert(num, fieldQuery.value);
            }
            else if (fieldQuery.method == "delete_by_index") 
            {
                stringstream ss(fieldQuery.value);
                int num;
                ss >> num;
                array.delete_by_index(num);
            }
            else if (fieldQuery.method == "replace_by_index") 
            {
                stringstream ss(fieldQuery.index);
                int num;
                ss >> num;
                array.replace_by_index(num, fieldQuery.value);
            }
            else if (fieldQuery.method == "print") 
            {
                array.print();
            }
            array.writeToConfiguration(fieldQuery.filePath);
            break;
        }
        case 'Q': // Очередь
        {
    //         if(fieldQuery.name != "myqueue")
    //         {
    //             cerr<<"Ошибка. Такой структуры "<<fieldQuery.name<<" не существует"<<endl;
    //             return;
    //         }
    // Queue<string> queue;
   
    //         queue.readingConfiguration(fieldQuery.filePath);
    //         if (fieldQuery.method == "push") 
    //         {
    //             queue.push_front(fieldQuery.value);
    //         } 
    //         else if (fieldQuery.method == "pop") 
    //         {
    //             queue.pop_back();
    //         } 
    //         else if (fieldQuery.method == "getSize") 
    //         {
    //             queue.pop_back();
    //         } 
    //         else if (fieldQuery.method == "print") 
    //         {
    //             queue.printQueue();
    //         }
    //         else
    //         {
    //             cout<<"Такого метода для очереди нет "<<fieldQuery.method<<endl;
    //         }
    //         queue.writeToConfiguration(fieldQuery.filePath);
    //         break;
        }
        case 'S': // Стек
        {
            if(fieldQuery.name != "mystack")
            {
                cerr<<"Ошибка. Такой структуры "<<fieldQuery.name<<" не существует"<<endl;
                return;
            }
    Stack<string> stack;
   
            stack.readingConfiguration(fieldQuery.filePath);
            if (fieldQuery.method == "push") 
            {
                stack.push_front(fieldQuery.value);
            } 
            else if (fieldQuery.method == "pop") 
            {
                stack.pop_front();
            } 
             else if (fieldQuery.method == "getSize") 
            {
                stack.pop_front();
            } 
            else if (fieldQuery.method == "print") 
            {
                stack.printStack();
            }
            stack.writeToConfiguration(fieldQuery.filePath);
            break;
        }
        case 'L': // Связанный список
        {
            if(fieldQuery.name != "mylist")
            {
                cerr<<"Ошибка. Такой структуры "<<fieldQuery.name<<" не существует"<<endl;
                return;
            }
            LinkedList<string> List;
            List.readingConfiguration(fieldQuery.filePath);
            if (fieldQuery.method == "getSize") 
            {
                cout<<List.getSize()<<endl;
            } 
            else if (fieldQuery.method == "push_back") 
            {
               List.push_back(fieldQuery.value);
            } 
            else if (fieldQuery.method == "push_front") 
            {
               List.push_front(fieldQuery.value);
            }
            else if (fieldQuery.method == "pop_back") 
            {
               List.pop_back();
            }
            else if (fieldQuery.method == "search_by_value") 
            {
               List.pop_back();
            }
            else if (fieldQuery.method == "pop_front") 
            {
               List.pop_front();
            }
            else if (fieldQuery.method == "delete_by_value") 
            {
               List.delete_by_value(fieldQuery.value);
            }
            else if (fieldQuery.method == "print") 
            {
               List.printList();
            }
            List.writeToConfiguration(fieldQuery.filePath);
            List.~LinkedList();
            break;
        }
        case 'D': // Двусвязный список
        {
             if(fieldQuery.name != "mydlist")
            {
                cerr<<"Ошибка. Такой структуры "<<fieldQuery.name<<" не существует"<<endl;
                return;
            }
            DLinkedList<string> DList;
   
            DList.readingConfiguration(fieldQuery.filePath);
            if (fieldQuery.method == "getSize") 
            {
                DList.getSize();
            }  
            else if (fieldQuery.method == "push_back") 
            {
                DList.push_back(fieldQuery.value);
            } 
            else if (fieldQuery.method == "push_front") 
            {
                DList.push_front(fieldQuery.value);
            }
            else if (fieldQuery.method == "pop_back") 
            {
                DList.pop_back();
            }
            else if (fieldQuery.method == "pop_front") 
            {
                DList.pop_front();
            }
            else if (fieldQuery.method == "search_by_value") 
            {
                DList.search_by_value(fieldQuery.value);
            }
            else if (fieldQuery.method == "delete_by_value") 
            {
                DList.delete_by_value(fieldQuery.value);
            }
            else if (fieldQuery.method == "print") 
            {
                DList.printList();
            }
            DList.writeToConfiguration(fieldQuery.filePath);
            break;
        }
        default:
            cerr << "Unknown structure type." << endl;
            break;
    }
}

bool ParseQuery::isValidCommand(const string& command) 
{
    regex pattern(R"(--file\s+(\S+)\s+--query\s+'([TMLDSQ][a-zA-Z_]+[a-zA-Z])\s+(\w+)(\s+[a-zA-Z0-9]+)?(\s+\d*)?'|\s*--man)");
    return regex_match(command, pattern);
}

void ParseQuery::parseCommand(const string& command) 
{
    FieldQuery fieldQuery;

    if (!isValidCommand(command))
    {
        cerr << "Invalid command format." << endl;
        return;
    }
   
    if (command.find("--man") != string::npos) 
    {
        cout << "Шаблоны команд: --file <name file> --query '<Structure Type><Method Structure> <namestruct> <value>' "
        <<" - для всех структур кроме отдельных методов массива. \n\nШаблоны команд для особых методов массива:\n\nПолучение по индексу: "
        <<" get_by_index (--file <name file> --query '<Structure Type><Method Structure> <namestruct> <index>')\n\n"
        <<"Вставка по индексу: insert_by_index (--file <name file> --query '<Structure Type><Method Structure> <namestruct> <value> <index>')\n\n"
        <<"Удаление по индексу delete_by_index (--file <name file> --query '<Structure Type><Method Structure> <namestruct> <index>')\n\n"
        <<"Смена по индексу replace_by_index (--file <name file> --query '<Structure Type><Method Structure> <namestruct> <value> <index>')\n\n"
        <<"-------------------------------------------- Methods Linked List -------------------------------------------- \n\n" 
        <<"getSize, push_back, push_front, search_by_value, pop_back, pop_front, delete_by_value, print\n\n"
        <<"-------------------------------------------- Methods Doubley Linked List -------------------------------------------- \n\n" 
        <<"getSize, push_back, push_front, search_by_value, pop_back, pop_front, delete_by_value, print\n\n"
        <<"-------------------------------------------- Methods Stack -------------------------------------------- \n\n" 
        <<"getSize, push, pop, print\n\n"
        <<"-------------------------------------------- Methods Queue -------------------------------------------- \n\n" 
        <<"getSize, push, pop, print\n\n"
        <<"-------------------------------------------- Methods array -------------------------------------------- \n\n" 
        <<"getSize,get_by_index, push_back, insert_by_index, delete_by_index, replace_by_index, print\n\n"
        
                <<"-------------------------------------------- ComBintree-------------------------------------------- \n\n" 
        <<"find, complete, push, print\n\n"<< endl;
        
        return;
    }
    smatch match;
    regex_search(command, match, regex(R"(--file\s+(\S+)\s+--query\s+'([TMLDSQ][a-zA-Z_]+[a-zA-Z])\s+(\w+)(\s+\w+)?(\s+\w+)?'|\s*--man)"));


  
    fieldQuery.filePath = match[1].str(); 
    fieldQuery.structureType = match[2].str()[0]; 
    fieldQuery.method = match[2].str().substr(1); 
    fieldQuery.name = match[3]; 

    
    if (match[4].length() > 0) 
    {
        fieldQuery.value = match[4].str(); 
        fieldQuery.value.erase(0, fieldQuery.value.find_first_not_of(' '));
    } 
    else 
    {
        fieldQuery.value = ""; 
    }

    if (match[5].length() > 0) 
    {
        fieldQuery.index = match[5].str();
    }
    if (fieldQuery.structureType != 'M' && !fieldQuery.index.empty()) 
    {
        cerr << "Ошибка запроса. Индекс может использоваться только для массива." << endl;
        return;
    }   
    string validStructTypes = "TMLDQS";

    if (validStructTypes.find(fieldQuery.structureType) == string::npos) 
    {
        cerr << "Такой структуры " << fieldQuery.structureType << " нет" << endl;
        return;
    }

    if(fieldQuery.method == "pop" || fieldQuery.method == "pop_front" || fieldQuery.method == "pop_back" && !fieldQuery.value.empty())
    {
        cerr<<"Ошибка. Методы pop не принимают в запросе значение"<<endl;

    }
    if(fieldQuery.method == "print" && !fieldQuery.value.empty())
    {
        cerr<<"Ошибка. Методы print без значений"<<endl;
    }
    if(fieldQuery.method == "get_by_index" && !fieldQuery.index.empty())
    {
        cerr<<"Следующее поле при получении индекса должно быть пустым"<<endl;
        return;
    }
    if(fieldQuery.method == "delete_by_index" && !fieldQuery.index.empty())
    {
        cerr<<"Следующее поле при удалении по индексу должно быть пустым"<<endl;
        return;
    }

    handleCommand(fieldQuery);
}