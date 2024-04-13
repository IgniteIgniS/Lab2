#include <iostream>
#include "MyString.h"


int main()
{
    Mystring string("main.txt");//нужно переделать конструктор через get и addstring
    std::cout << string.FindSubstring("q") << std::endl;
    //std::cout << string.CountWords();
    //Mystring string1("add_to_file.txt");
    //string1.ShowString();
    //std::cout << "========================================" << '\n';
    //string = string1;
    //string.ShowString();
    //string.output_to_csv("result_csv.csv");
}
