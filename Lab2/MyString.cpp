#include "MyString.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <cctype>
#include <map>
#include <algorithm>

Mystring::Mystring()
{
	data = new char[1];
	data[0] = '\0';
	len = 0;
}

Mystring::Mystring(const char* path)
{
    std::ifstream fin(path);
    if (!fin.is_open())
    {
        std::cout << "Error" << std::endl;
        data = nullptr;
        return;
    }

    char symbol;
    while (fin >> std::noskipws >> symbol)
    {
        ++len;
    }

    fin.clear();
    fin.seekg(0, std::ios::beg);

    data = new char[len + 1];
    int i = 0;
    while (i < len && fin >> std::noskipws >> symbol) // пропускает пробелы в начале - std::noskipws
    {
        data[i++] = symbol;
    }
    data[i] = '\0';

    fin.close();
}

Mystring::~Mystring()
{
    delete[] data;
}

void Mystring::ShowString()
{
    if (this->data != nullptr) {
        std::cout << this->data << std::endl;
    }
}

char* Mystring::AddString(const char* path)
{
    std::ifstream fin(path);
    if (!fin.is_open())
    {
        return nullptr;
    }

    char symbol;
    int size = 0;
    while (fin >> std::noskipws >> symbol)
    {
        ++size;
    }

    fin.clear();
    fin.seekg(0, std::ios::beg);

    char* addData = new char[size + 1];
    int i = 0;
    while (i < size && fin >> std::noskipws >> symbol) {
        addData[i++] = symbol;
    }
    addData[i] = '\0';

    fin.close();

    char* newData = new char[len + size + 1];

    for (size_t i = 0; i < len; i++)
    {
        newData[i] = data[i];
    }

    for (size_t i = 0; i < size; i++)
    {
        newData[len + i] = addData[i];
    }

    newData[len + size] = '\0';

    delete[] data;
    delete[] addData;
    data = newData;
    len += size;
    return data;
}

void Mystring::Output_to_txt(const char* path)
{
    std::ofstream fout(path);
    if (!fout.is_open())
    {
        std::cout << "Unable to open file";
        return;
    }

    fout << data;
    fout.close();
}

void Mystring::Output_to_csv(const char* path)
{
    std::ofstream fout(path);
    if (!fout.is_open())
    {
        std::cout << "Unable to open file";
        return;
    }

    for (size_t i = 0; i < len; i++)
    {
        if (data[i] == ' ')
        {
            fout << ';';
        }
        else
        {
            fout << data[i];
        }
    }
    fout.close();
}

size_t Mystring::Stringlen(const char* string)
{
    size_t length = 0;
    while (*string != '\0')
    {
        length++;
        string++;
    }
    return length;
}

Mystring& Mystring::operator=(const Mystring& other)
{
    if (this != &other) // предотвращение самоприсваивания
    {
        delete[] data; // удаление существующих данных

        len = other.len; 
        data = new char[len + 1]; 

        for (size_t i = 0; i < len; i++) 
        {
            data[i] = other.data[i];
        }

        data[len] = '\0'; 
    }

    return *this; 
}

int Mystring::CountWords()
{
    int wordCount = 0;
    bool inWord = false;
    bool isHyphen = false;//дефис

    for (size_t i = 0; i < len; i++)
    {
        // Проверка на символы, разделяющие слова
        if (data[i] == ' ' || data[i] == '\n' || data[i] == '\t')
        {
            if (inWord)
            {
                wordCount++;
                inWord = false;
            }
            continue;  // Пропускаем дополнительные пробелы и табуляции
        }
        else if (data[i] == '-' && !isHyphen)  // Проверка на тире; если это тире, но не дефис
        {
            isHyphen = true;
            continue;
        }
        isHyphen = false;
        if (!inWord) // Если текущий символ не является разделителем, присваиваем статус слова
        {
            inWord = true;
        }
    }
    // Добавляем последнее слово, если строка не заканчивается разделителем
    if (inWord)
    {
        wordCount++;
    }

    return wordCount;
}

int Mystring::FindSubstring(const char* substring)
{
    size_t subLen = Stringlen(substring);

    for (int i = 0; i <= len - subLen; i++) // -subLen чтобы не выходить за границы строки
    {
        bool found = true;

        for (size_t j = 0; j < subLen; j++)
        {
            if (data[i + j] != substring[j])
            {
                found = false;
                break;
            }
        }

        if (found)
        {
            return i; // индекс первого вхождения подстроки
        }
    }

    return -1; // подстрока не найдена
}

void Mystring::toLowerCase(char* str)
{
    for (size_t i = 0; str[i]; i++)
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
        {
            str[i] = str[i] - 'A' + 'a';
        }
    }
}

void Mystring::myStrCpy(char* current, const char* source)
{
    while (*source != '\0')
    {
        *current = *source;
        current++;
        source++;
    }
    *current = '\0';
}

int Mystring::myStrcmp(const char* str1, const char* str2)
{
    while (*str1 && (*str1 == *str2))
    {
        str1++;
        str2++;
    }
    return *str1 - *str2;//unsigned char не обязательна при использование таблицы аски
}

int Mystring::CountUniqueWords(WordCount** results)
{
    if (*results != nullptr) {
        for (int i = 0; i < size; ++i)
        {
            delete[](*results)[i].word;
        }
        delete[] * results;
    }
    *results = new WordCount[len]; // массив для хранения результатов
    int size = 0; // количество уникальных слов

    char* word = new char[len + 1];
    size_t j = 0;
    for (size_t i = 0; i <= len; i++)
    {
        if (data[i] == ' ' || data[i] == '\n' || data[i] == '\t' || data[i] == ',' || data[i] == '.' || data[i] == '\0' || data[i] == '"' || data[i] == '!' || data[i] == '?')
        {
            if (j != 0)
            {
                word[j] = '\0';
                toLowerCase(word);

                // Проверяем, есть ли слово уже в results
                bool found = false;
                for (int k = 0; k < size; k++)
                {
                    if (myStrcmp((*results)[k].word, word) == 0) // формирует word, а потом проверяет с существующим (*results)[k].word
                    {
                        (*results)[k].count++;
                        found = true;
                        break;
                    }
                }

                // Если слова нет в results, добавляем его
                if (!found)
                {
                    (*results)[size].word = new char[j + 1]; //(*results)[size].word обращаемся в структуру 
                    myStrCpy((*results)[size].word, word);
                    (*results)[size].count = 1;
                    size++;
                }
                j = 0;
            }
        }
        else
        {
            word[j++] = data[i];
        }
    }


    return size; // возвращаем количество уникальных слов
}

//WordCount* Mystring::CountUniqueWords(int* size)
//{
//    if (results != nullptr) {
//        for (int i = 0; i < *size; ++i)
//        {
//            delete[] results[i].word;
//        }
//        delete[] results;
//    }
//    results = new WordCount[len]; // массив для хранения результатов
//    int uniqueWordCount = 0; // количество уникальных слов
//
//    char* word = new char[len + 1];
//    size_t j = 0;
//    for (size_t i = 0; i <= len; i++)
//    {
//        if (data[i] == ' ' || data[i] == '\n' || data[i] == '\t' || data[i] == ',' || data[i] == '.' || data[i] == '\0' || data[i] == '"' || data[i] == '!' || data[i] == '?')
//        {
//            if (j != 0)
//            {
//                word[j] = '\0';
//                toLowerCase(word);
//
//                // Проверяем, есть ли слово уже в results
//                bool found = false;
//                for (int k = 0; k < uniqueWordCount; k++)
//                {
//                    if (myStrcmp(results[k].word, word) == 0) // формирует word, а потом проверяет с существующим results[k].word
//                    {
//                        results[k].count++;
//                        found = true;
//                        break;
//                    }
//                }
//
//                // Если слова нет в results, добавляем его
//                if (!found)
//                {
//                    results[uniqueWordCount].word = new char[j + 1]; //results[uniqueWordCount].word обращаемся в структуру 
//                    myStrCpy(results[uniqueWordCount].word, word);
//                    results[uniqueWordCount].count = 1;
//                    uniqueWordCount++;
//                }
//                j = 0;
//            }
//        }
//        else
//        {
//            word[j++] = data[i];
//        }
//    }
//
//    *size = uniqueWordCount; // обновляем значение size
//    return results; // возвращаем указатель на результаты
//}

void Mystring::SortByFrequency(WordCount* results, int size, bool ascending)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            bool shouldSwap;
            if (ascending) //возрастание
            {
                shouldSwap = (results[j].count > results[j + 1].count);
            }
            else 
            {
                shouldSwap = (results[j].count < results[j + 1].count);
            }

            if (shouldSwap)
            {
                std::swap(results[j], results[j + 1]);
            }
        }
    }
}

void Mystring::SortAlphabetically(WordCount* results, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (myStrcmp(results[j].word, results[j + 1].word) > 0)
            {
                WordCount temp = results[j];
                results[j] = results[j + 1];
                results[j + 1] = temp;
            }
        }
    }
}

Mystring::Mystring(const Mystring& other) 
{
    len = other.len;
    data = new char[len + 1];
    for (size_t i = 0; i < len; i++) {
        data[i] = other.data[i];
    }
    data[len] = '\0';
}

//WordCount::~WordCount()
//{
//    delete[] word;
//} //примитивные данных типа count удаляются сами, когда выходят из видимости

void Mystring::OutputDictionary_to_txt(const char* path, WordCount** results, int size)
{
    std::ofstream fout(path);
    if (!fout.is_open())
    {
        std::cout << "Unable to open file";
        return;
    }

    for (int i = 0; i < size; i++)
    {
        fout << (*results)[i].word << ": " << (*results)[i].count << "\n";
    }
    fout.close();
}

void Mystring::OutputDictionary_to_csv(const char* path, WordCount** results, int size)
{
    std::ofstream fout(path);
    if (!fout.is_open())
    {
        std::cout << "Unable to open file";
        return;
    }

    for (int i = 0; i < size; i++)
    {
        fout << (*results)[i].word << ";" << (*results)[i].count << "\n";
    }
    fout.close();
}

void Mystring::ShowDictionary(WordCount* results, int size)
{
    for (int i = 0; i < size; i++)
    {
        std::cout << results[i].word << ": " << results[i].count << "\n";
    }
}
