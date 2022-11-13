#include <string>
#include <iostream>
#include "Loader.h"
using namespace std; 

int main()
{
    string filePath = "D:\\Prog\\Luna\\Text.json";
    cout << "Hello World!\n" << filePath<<endl;
    Loader a = Loader(filePath);
    a.DoSome();
}
