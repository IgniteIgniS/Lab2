#include <iostream>
#include "MyString.h"


int main()
{
    setlocale(LC_ALL, "Russian");
    Mystring string("add_to_file.txt");
    WordCount* results;
    int size = string.CountUniqueWords(&results);
    for (int i = 0; i < size; i++)
    {
        std::cout << (*results)[i].word << ": " << (*results)[i].count << "\n";
    }
    string.SortByFrequency(&results, size, true);
    string.OutputDictionary_to_txt("sorted_dictionary.txt", &results, size);

    //string.SortByFrequency(&results, size, false);

    //int uniqueWordCount = string.CountUniqueWords(&results); // Вызываем метод CountUniqueWords
    //string.ShowString();


    //std::cout << string.FindSubstring("пошли?") << std::endl;
    //std::cout << string.CountWords();
    //Mystring string1("add_to_file.txt");
    //string1.ShowString();
    //std::cout << "========================================" << '\n';
    //string = string1;
    //string.ShowString();
    //string.output_to_csv("result_csv.csv");
}
