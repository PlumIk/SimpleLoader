#include <string>
#include <iostream>
#include "Loader.h"
using namespace std; 

int main()
{
    string filePath = "D:\\Prog\\Luna\\Text.json";
    cout << "I test\n" << filePath<<endl;
    Loader a = Loader(filePath);
    a.DoSome();

    int one = a.GetInt("one");
    double two = a.GetDouble("two");
    cout << one + two << " " << a.GetString("three")<<endl;
    int* intMas = a.GetIntMas("four");
    for (int i = 0; i < a.GetMasSize("four"); i++) {
        cout << intMas[i] << " ";
    }
    cout << endl;
    double* doubleMas = a.GetDoubleMas("five");
    for (int i = 0; i < a.GetMasSize("five"); i++) {
        cout << doubleMas[i] << " ";
    }
    cout << endl;
    string* stringeMas = a.GetStringMas("six");
    for (int i = 0; i < a.GetMasSize("six"); i++) {
        cout << stringeMas[i] << " ";
    }
    cout << endl;
    intMas = a.GetIntMas("7");
    for (int i = 0; i < a.GetMasSize("7"); i++) {
        cout << intMas[i] << " ";
    }
    cout << endl;
    doubleMas = a.GetDoubleMas("8");
    for (int i = 0; i < a.GetMasSize("8"); i++) {
        cout << doubleMas[i] << " ";
    }
    cout << endl;
}
