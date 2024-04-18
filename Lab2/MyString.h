#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <cctype>
#include <map>
#include <algorithm>

struct WordCount 
{
	WordCount() = default;
	WordCount(WordCount &&other)
	{
		this->word = other.word;
		this->count = other.count;
		other.word = nullptr;
		other.count = 0;
	}
	void operator=(WordCount &&other)
	{
		this->word = other.word;
		this->count = other.count;
		other.word = nullptr;
		other.count = 0;
	}
	~WordCount()
	{
		delete[] word;
	}
	friend class Mystring;
private:
	char* word = nullptr;
	int count = 0;
};

class Mystring
{
public:
	Mystring();
	Mystring(const char* path);
	Mystring(const Mystring& other);
	~Mystring();

	void ShowString();
	Mystring AddString(const char* path);

	void Output_to_txt(const char* path);
	void Output_to_csv(const char* path);//������

	Mystring& operator=(const Mystring& other);

	int CountWords();

	int FindSubstring(const char* substring);

	int CountUniqueWords(WordCount*& results);

	void ShowDictionary(WordCount* results);

	void SortByFrequency(WordCount* results, bool ascending);

	void SortAlphabetically(WordCount* results);

	void OutputDictionary_to_txt(const char* path, WordCount* results);

	void OutputDictionary_to_csv(const char* path, WordCount* results);

private:
	char* data;
	size_t len = 0; //len - ���������� ��������
	int size = 0;
	void toLowerCase(char* str);
	void myStrCpy(char* current, const char* source);
	int myStrcmp(const char* str1, const char* str2);
	size_t Stringlen(const char* string);

};


