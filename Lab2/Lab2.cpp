#include <iostream>
#include "MyString.h"

void not_change(int chislo) {
    chislo = chislo * 10;
}

void change(int &chislo) {
    chislo = chislo * 10;
}

int changed(int chislo) {
    return chislo * 10;
}

int main()
{
    // Mystring string("main1.txt");
    // WordCount* results = nullptr;

    // //std::cout << string.CountWords();
    // //std::cout << string.FindSubstring("hell");
    
    // /*string.AddString("add_to_file.txt");
    // string.ShowString();*/

    // int size = string.CountUniqueWords(results);
    // string.ShowDictionary(results);
    // std::cout << "=============================================" << std::endl;
    // string.SortByFrequency(results, true);
    // string.ShowDictionary(results);
    // std::cout << "=============================================" << std::endl;
    // string.SortAlphabetically(results);
    // string.ShowDictionary(results);
    // //string.OutputDictionary_to_csv("result.csv", results, size);
    // //string.OutputDictionary_to_csv("result.csv", &results, size);
    int a = 1;
    not_change(a);
    std::cout << "Not change a: " << a << '\n';
    std::cout << "Changed copy of a: " << changed(a) << '\n';
    std::cout << "After changing copy a: " << a << '\n';
    change(a);
    std::cout << "Change a: " << a << '\n';
    
}
