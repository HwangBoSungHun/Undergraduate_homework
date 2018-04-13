
#ifndef IGCalculator_hpp
#define IGCalculator_hpp

#include <stdio.h>
#include <math.h>
#include <vector>

using namespace std;

typedef struct IG_Info
{
    float fAttr_value;
    double dIG_value;
}IG_Info;

//한가지에 대해서만 엔트로피를 구할 때 사용하는 function.
double Entropy1(float arr[], int nSize);

//두가지 요소 간에 엔트로피를 구할 때 사용하는 function.
double Entropy2(vector<float> const& arr1, float arr2[], int nSize);

//information gain을 구하는 function.
double IG(double dEnt1, double dEnt2);

//(Sorting 하지 않음) 한 attribute에 대한 column이 들어왔을 때, 그 column을 기준으로 모든 value의 IG을 구해서 IG이 가장 큰 것의 정보를 저장.
IG_Info MaxIG_Info(float fRorW[], float fAttr[], int nSize);

#endif /* IGCalculator_hpp */

