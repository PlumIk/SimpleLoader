#include <string>
#include <iostream>
#include "Loader.h"
#include "ParamsBase.h"
using namespace std; 

int main()
{
    string filePath = "D:\\Prog\\Luna\\Text.json";
    cout << "I test\n" << filePath<<endl;

    ParamsBase a = ParamsBase(filePath);

    a.DoSome();
    int max = a.GetInt("one");
    for (int i = 0; i < 10; i++) {
        cout << endl << "Start with "<<max<<endl;
        for (int j = 0; j < max; j++) {
            cout << a.GetString("two") << endl;
        }
        cout << "End";
        a.DoSome();
        a.Update();
        if (a.GetIsChange()) {
            max = a.GetInt("one");
        }
    }

    //int one = a.GetInt("one");
    //double two = a.GetDouble("two");
    //cout << one + two << " " << a.GetString("three")<<endl;
    //int* intMas = a.GetIntMas("four");
    //for (int i = 0; i < a.GetMasSize("four"); i++) {
    //    cout << intMas[i] << " ";
    //}
    //cout << endl;
    //double* doubleMas = a.GetDoubleMas("five");
    //for (int i = 0; i < a.GetMasSize("five"); i++) {
    //    cout << doubleMas[i] << " ";
    //}
    //cout << endl;
    //string* stringeMas = a.GetStringMas("six");
    //for (int i = 0; i < a.GetMasSize("six"); i++) {
    //    cout << stringeMas[i] << " ";
    //}
    //cout << endl;
    //intMas = a.GetIntMas("7");
    //for (int i = 0; i < a.GetMasSize("7"); i++) {
    //    cout << intMas[i] << " ";
    //}
    //cout << endl;
    //doubleMas = a.GetDoubleMas("8");
    //for (int i = 0; i < a.GetMasSize("8"); i++) {
    //    cout << doubleMas[i] << " ";
    //}
    //cout << endl;
    

}
