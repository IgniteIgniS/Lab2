#pragma once
struct WordCount 
{
	char* word;
	int count;
};

class Mystring
{
public:
	Mystring();
	Mystring(const char* path); // 	Mystring(const char* str); - спросить, хорошая ли это идея?(конструктор для определения непосредственно строки))
	Mystring(const Mystring& other);
	~Mystring();

	void ShowString();
	char* AddString(const char* path);

	void Output_to_txt(const char* path);
	void Output_to_csv(const char* path);

	Mystring& operator=(const Mystring& other);

	int CountWords();

	size_t Stringlen(const char* string);
	int FindSubstring(const char* substring);

	void toLowerCase(char* str);
	void myStrCpy(char* current, const char* source);

	int myStrcmp(const char* str1, const char* str2);

	int CountUniqueWords(WordCount** results);
	void ShowDictionary(WordCount* results, int size);

	void SortByFrequency(WordCount* results, int size, bool ascending);

	void SortAlphabetically(WordCount* results, int size);

	void OutputDictionary_to_txt(const char* path, WordCount** results, int size);

	void OutputDictionary_to_csv(const char* path, WordCount** results, int size);


private:
	char* data;
	size_t len = 0; //len - количество символов
	WordCount* results = nullptr;
	int size = 0;
};


