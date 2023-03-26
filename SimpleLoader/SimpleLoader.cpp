#include <string>
#include <iostream>
#include "Loader.h"
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


int main()
{
    string filePath = "D:\\Prog\\Luna\\RandomSearch.json";
    cout << "I test\n" << filePath<<endl;

    Loader* loader = new Loader(filePath);
    ParamsBase a = ParamsBase(loader);
    RandomSearch finder = RandomSearch(loader);
    int value = 32;
    vector<string> optimizeNamel;
    optimizeNamel.push_back("one");
    optimizeNamel.push_back("two");
    while (finder.IsEnd(value))
    {
        finder.TryOptimize(optimizeNamel);
        a.Update();
        cout << "Int value = " << a.GetInt("one") << ", Double value = " << a.GetDouble("two")<<endl;
        value = value / 2;
    }


    return 0;

}

void mainProg(Loader loader, ParamsBase a) {
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
    for (k = 0; k < Nt; k++) {
        test = 0;
        a.DoSome();
        a.Update();
        n = a.GetInt(VARIBLE_NAME);
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
        printf("Start in %d. Time %f.  ", n, end - start);
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
