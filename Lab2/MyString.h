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
	Mystring(const char* path); 
	Mystring(const Mystring& other);
	~Mystring();

	void ShowString();
	Mystring AddString(const char* path);

	void Output_to_txt(const char* path);
	void Output_to_csv(const char* path);//лишнее

	Mystring& operator=(const Mystring& other);

	int CountWords();

	int FindSubstring(const char* substring);

	int CountUniqueWords(WordCount** results);// существует так как работает с копией
	//int CountUniqueWords(WordCount* results);
	void ShowDictionary(WordCount* results, int size);

	void SortByFrequency(WordCount* results, int size, bool ascending);

	void SortAlphabetically(WordCount* results, int size);

	void OutputDictionary_to_txt(const char* path, WordCount* results, int size);

	void OutputDictionary_to_csv(const char* path, WordCount* results, int size);

private:
	char* data;
	size_t len = 0; //len - количество символов
	int size = 0;
	void toLowerCase(char* str);
	void myStrCpy(char* current, const char* source);
	int myStrcmp(const char* str1, const char* str2);
	size_t Stringlen(const char* string);

};


