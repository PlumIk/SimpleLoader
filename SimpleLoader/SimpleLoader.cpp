#include <string>
#include <iostream>
#include "MainParamsBase.h"
#include "ParamsBase.h"
#include <cmath>
#include <fstream>
#include <immintrin.h>
#include <omp.h>
#include "RandomSearch.h"
#include "IFinder.h"

 float Xa ;
 float Xb ;
 float Ya ;
 float Yb ;
 int Nx ;
 int Ny ;
 int Nt ;
typedef unsigned long long MyTime;
float* RoMass;
float* F1;
float* F2;
__m256* VF1;
__m256* VF2;
__m256* VRoMass;

#define SAVE_VARIBLE_NAME(varible) VARIBLE_NAME = string(#varible);
string VARIBLE_NAME = "NULL";

void operationSuccsess(bool succsess) {
    if (succsess) {
        cout << "Succsess" << endl;
    }
    else {
        cout << "Cant do it" << endl;
    }
}

void mainProg() {
    string filePath = "D:\\Prog\\Luna\\Text.json";
    cout << "I test\n" << filePath << endl;
    MainParamsBase* params = new MainParamsBase(filePath);
    ParamsBase a = ParamsBase(params);
    RandomSearch finder = RandomSearch(params);
    SAVE_VARIBLE_NAME(Xa);
    Xa = a.GetDouble(VARIBLE_NAME);
    SAVE_VARIBLE_NAME(Xb);
    Xb = a.GetDouble(VARIBLE_NAME);
    SAVE_VARIBLE_NAME(Ya);
    Ya = a.GetDouble(VARIBLE_NAME);
    SAVE_VARIBLE_NAME(Yb);
    Yb = a.GetDouble(VARIBLE_NAME);
    SAVE_VARIBLE_NAME(Nx);
    Nx = a.GetInt(VARIBLE_NAME);
    SAVE_VARIBLE_NAME(Ny);
    Ny = a.GetInt(VARIBLE_NAME);
    SAVE_VARIBLE_NAME(Nt);
    Nt = a.GetInt(VARIBLE_NAME);
    int n;
    SAVE_VARIBLE_NAME(n);
    n = a.GetInt(VARIBLE_NAME);
    float hx = (Xb - Xa) / ((float)Nx - 1);
    float hy = (Yb - Ya) / ((float)Ny - 1);
    float* RoMass = (float*)calloc(Ny * Nx, sizeof(float));
    int i, j;
    float Xs1 = Xa + ((Xb - Xa) / ((float)3));
    float Ys1 = Ya + ((Yb - Ya) * ((float)2) / ((float)3));
    float Xs2 = Xa + ((Xb - Xa) * ((float)2) / ((float)3));
    float Ys2 = Ya + ((Yb - Ya) / ((float)3));
    float R = 0.1 * min(Xb - Xa, Yb - Ya);
    int offset;
    for (i = 0; i < Ny; i++) {
        offset = i * Nx;
        for (j = 0; j < Nx; j++) {
            if ((pow((Xa + hx * j - Xs1), 2) + pow((Ya + hy * i - Ys1), 2)) < pow(R, 2)) {
                RoMass[offset + j] = 0.1;
            }
            else if (pow((Xa + hx * j - Xs2), 2) + pow((Ya + hy * i - Ys2), 2) < pow(R, 2)) {
                RoMass[offset + j] = -0.1;
            }
        }
    }

    float* F1 = (float*)calloc(Ny * Nx, sizeof(float));
    float* F2 = (float*)calloc(Ny * Nx, sizeof(float));
    float const1 = ((float)1) / (((float)5) * (((float)1) / (pow(hx, 2)) + ((float)1) / (pow(hy, 2))));
    float const2 = (((float)1) / ((float)2)) * (((float)5) / (pow(hx, 2)) - ((float)1) / (pow(hy, 2)));
    float const3 = (((float)1) / ((float)2)) * (((float)5) / (pow(hy, 2)) - ((float)1) / (pow(hx, 2)));
    float const4 = (((float)1) / ((float)4)) * (((float)1) / (pow(hx, 2)) + ((float)1) / (pow(hy, 2)));
    float const5 = ((float)1) / ((float)4);
    float test;
    int k;
    vector<string> optimizeNamel;
    optimizeNamel.push_back("n");
    double value = 0;
    bool skip = false;
    for (k = 0; k < Nt; k++) {
        test = 0;
        if (value != 0 && !skip) {
            if (finder.IsEnd(value))
            {
                finder.TryOptimize(optimizeNamel);
                a.Update();
            }
            else {
                finder.selectBestSuggest();
                a.Update();
                skip = true;
            }
            n = a.GetInt(VARIBLE_NAME);
        }
        omp_set_dynamic(0);
        omp_set_num_threads(n);
        double start = omp_get_wtime();
#pragma omp parallel for  private(j, offset) 
        for (i = 1; i < Ny - 1; i++) {
            offset = i * Nx;
            for (j = 1; j < Nx - 1; j++) {
                F2[offset + j] = const1 * (const2 * (F1[offset + j - 1] + F1[offset + j + 1])
                    + const3 * (F1[offset + j - Nx] + F1[offset + j + Nx]) +
                    const4 * (F1[offset + j - Nx - 1] + F1[offset + j - Nx + 1] + F1[offset + j + Nx - 1] + F1[offset + j + Nx + 1]) +
                    ((float)2) * RoMass[offset + j] +
                    const5 * (RoMass[offset + j - Nx] + RoMass[offset + j + Nx] + RoMass[offset + j - 1] + RoMass[offset + j + 1]));
            }
        }
        double end = omp_get_wtime();
        value = end - start;
        printf("Start in %d. Time %f. ", n, value);
        for (i = 1; i < Ny - 1; i++) {
            offset = i * Nx;
            for (j = 1; j < Nx - 1; j++) {
                F1[offset + j] = F2[offset + j];

            }
        }
        free(F2);
        F2 = (float*)calloc(Ny * Nx, sizeof(float));
    }
}

void newLogic() {
    string filePath = "D:\\Prog\\Luna\\SimpleLoader\\SimpleLoader\\NewFormat.json";
    cout << "I test\n" << filePath << endl;
    MainParamsBase* params = new MainParamsBase(filePath);
    cout << "Work with int value one." << endl;
    vector<int> intV = params->GetIntRestrictions("one");
    cout <<"Name:one." << "Value:"<<params->GetInt("one") << ". Restrictions:" << intV[0] << " - " << intV[1];
    intV = params->GetIntPosible("one","value1");
    cout << ". Posible: " << intV[0] << " - " << intV[1] << endl;
    cout << "Try set value 5. ";
    operationSuccsess(params->SetInt("one", 5));
    cout << "Try set value 2. ";
    operationSuccsess(params->SetInt("one", 2));
    cout << "Name:one." << "Value:" << params->GetInt("one") << endl <<endl;

    vector<double> doubleV = params->GetDoubleRestrictions("two");
    cout << "Name:two." << "Value:" << params->GetDouble("two") << ". Restrictions:" << doubleV[0] << " - " << doubleV[1];
    doubleV = params->GetDoublePosible("two", "value1");
    cout << ". Posible: " << doubleV[0] << " - " << doubleV[1] << endl;
    cout << "Try set value 5. ";
    operationSuccsess(params->SetDouble("two", 5));
    cout << "Try set value 2. ";
    operationSuccsess(params->SetDouble("two", 2));
    cout << "Name:two." << "Value:" << params->GetDouble("two") << endl << endl;

    cout << "Try get info about three" << endl;
    intV = params->GetIntRestrictions("three");
    if (intV.size() == 0) {
        cout << "Empty res for three" << endl;
    }
    else {
        throw new exception("Empty restriction");
    }
    intV = params->GetIntPosible("three","value1");
    if (intV.size() == 0) {
        cout << "Empty posible for three" << endl;
    }
    else {
        throw new exception("Empty restriction");
    }

    cout << "Set info about four. It will be double with value 2.5. " ;
    operationSuccsess(params->AddDoubleVar("four", 2.5));
    cout << "Set restriction -1 - 17. ";
    vector<double> vec;
    vec.push_back(-1);
    vec.push_back(17);
    operationSuccsess(params->AddDoubleVarRestrictions("four", vec));
    cout << "Set posible -1,2,15. ";
    vector<double> vec2;
    vec2.push_back(-1);
    vec2.push_back(2);
    vec2.push_back(15);
    operationSuccsess(params->AddDoubleVarPosible("four", "value1", vec2));
    vec = params->GetDoublePosible("four", "value1");
    if (vec.size() == 3) {
        cout << "Posible: " << vec[0] << "," << vec[1] <<"," << vec[2] << endl;
    }
    else {
        throw new exception("Empty restriction");
    }
    vec = params->GetDoubleRestrictions("four");
    if (vec.size() == 2) {
        cout << "Restrictions:" << vec[0] << " - " << vec[1] << endl;
    }
    else {
        throw new exception("Empty restriction");
    }
    cout << "Name:four." << "Value:" << params->GetDouble("four") << endl << endl;
}


int main()
{
    newLogic();
    //mainProg();
}
