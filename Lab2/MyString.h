#pragma once
class Mystring
{
public:
	Mystring();
	Mystring(const char* path); // 	Mystring(const char* str); - спросить, хорошая ли это идея?
	~Mystring();

	void ShowString();
	char* AddString(const char* path);

	void Output_to_txt(const char* path);
	void Output_to_csv(const char* path);

	Mystring& operator=(const Mystring& other);

	int CountWords();

	size_t Stringlen(const char* string);
	int FindSubstring(const char* substring);

	int myStrcmp(const char* str1, const char* str2);
	void CountUniqueWords();



private:
	char* data;
	size_t len = 0; //len - количество символов
};


