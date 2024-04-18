#include <iostream>
#include "MyString.h"

int main()
{
    Mystring string("main1.txt");
    WordCount* results = nullptr;

    //std::cout << string.CountWords();
    //std::cout << string.FindSubstring("hell");
    
    /*string.AddString("add_to_file.txt");
    string.ShowString();*/

    int size = string.CountUniqueWords(&results);
    string.ShowDictionary(results, size);
    std::cout << "=============================================" << std::endl;
    string.SortByFrequency(results, size, false);
    string.ShowDictionary(results, size);
    //string.SortAlphabetically(results, size);
    //string.ShowDictionary(results, size);
    //string.OutputDictionary_to_csv("result.csv", results, size);
    //string.OutputDictionary_to_csv("result.csv", &results, size);
}
