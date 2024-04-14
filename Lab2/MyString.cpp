#include "MyString.h"
#include <fstream>
#include <iostream>
#include <map>

Mystring::Mystring()
{
	//this->data = nullptr;
	data = new char[1];
	data[0] = '\0';
	len = 0;
}

Mystring::Mystring(const char* path)
{
    std::ifstream fin(path);
    if (!fin.is_open())
    {
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
    while (i < len && fin >> std::noskipws >> symbol) // ���������� ������� � ������ - std::noskipws
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
    if (this != &other) // �������������� ����������������
    {
        delete[] data; // �������� ������������ ������

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
    bool isHyphen = false;//�����

    for (size_t i = 0; i < len; i++)
    {
        // �������� �� �������, ����������� �����
        if (data[i] == ' ' || data[i] == '\n' || data[i] == '\t')
        {
            if (inWord)
            {
                wordCount++;
                inWord = false;
            }
            continue;  // ���������� �������������� ������� � ���������
        }
        else if (data[i] == '-' && !isHyphen)  // �������� �� ����; ���� ��� ����, �� �� �����
        {
            isHyphen = true;
            continue;
        }
        isHyphen = false;
        if (!inWord) // ���� ������� ������ �� �������� ������������, ����������� ������ �����
        {
            inWord = true;
        }
    }
    // ��������� ��������� �����, ���� ������ �� ������������� ������������
    if (inWord)
    {
        wordCount++;
    }

    return wordCount;
}

int Mystring::FindSubstring(const char* substring)
{
    size_t subLen = Stringlen(substring);

    for (int i = 0; i <= len - subLen; i++) // -subLen ����� �� �������� �� ������� ������
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
            return i; // ������ ������� ��������� ���������
        }
    }

    return -1; // ��������� �� �������
}

// ��������������� ������� ��� �������������� ������ � ������ �������
void toLowerCase(char* str)
{
    for (size_t i = 0; str[i]; i++)
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
        {
            str[i] = str[i] - 'A' + 'a'; //�������� �� ������� ���� 
        }
    }
}

void myStrCpy(char* current, const char* source)
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
    return *str1 - *str2;//unsigned char �� ����������� ��� ������������� ������� ����
}

void Mystring::CountUniqueWords()
{
    char** words = new char* [len]; // ������������ ���������� ���� ����� len
    int* counts = new int [len]; // ���������� ��������� ������� �����
    int size = 0; // ���������� ���������� ����

    char* word = new char[len + 1];
    size_t j = 0;//���������� ������� word
    for (size_t i = 0; i <= len; i++)
    {
        if (data[i] == ' ' || data[i] == '\n' || data[i] == '\t' || data[i] == ',' || data[i] == '.' || data[i] == '\0')
        {
            if (j != 0)
            {
                word[j] = '\0';
                toLowerCase(word);

                // ���������, ���� �� ����� ��� � words
                bool found = false;
                for (int k = 0; k < size; k++)
                {
                    if (myStrcmp(words[k], word) == 0)
                    {
                        counts[k]++;
                        found = true;
                        break;
                    }
                }

                // ���� ����� ��� � words, ��������� ���
                if (!found)
                {
                    words[size] = new char[j + 1];
                    myStrCpy(words[size], word);
                    words[size][j] = '\0'; // ��������� ������� ������ � ����� ������
                    counts[size] = 1;
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

    delete[] word;

    // ������� ���������
    for (int i = 0; i < size; i++)
    {
        std::cout << words[i] << " - " << counts[i] << std::endl;
        delete[] words[i];
    }

    delete[] words;
    delete[] counts;
}