#include "IGCalculator.hpp"
#include <stdio.h>
#include <math.h>
#include <vector>

#define SWAP(x, y) {float t = x; x = y; y = t;}

using namespace std;

//한가지에 대해서만 엔트로피를 구할 때 사용하는 function
double Entropy1(float arr[], int nSize)
{
    double dSumOf1 = 0;
    double dSumOf2 = 0;
    double dResult = 0;
    
    for (int i = 0; i < nSize; i++)
    {
        if (arr[i] == 1.0)
        {
            dSumOf1++;
        }
        else if (arr[i] == 2.0)
        {
            dSumOf2++;
        }
    }
    dResult = -( dSumOf1 / (dSumOf1 + dSumOf2)) * log2( dSumOf1 / (dSumOf1 + dSumOf2)) - ( dSumOf2 / (dSumOf1 + dSumOf2)) * log2(dSumOf2 / (dSumOf1 + dSumOf2));
    
    return dResult;
}

//두가지 요소 간에 엔트로피를 구할 때 사용하는 function
double Entropy2(vector<float> const& arr1, float arr2[], int nSize)
{
    
    double dResult = 0;
    double dSum[2][2] = {0};
    
    for (int i = 0; i < nSize; i++)
    {
        if (arr1[i] == 1.0 && arr2[i] == 1.0)
        {
            dSum[0][0]++;
        }
        
        else if (arr1[i] == 1.0 && arr2[i] == 2.0)
        {
            dSum[0][1]++;
        }
        
        else if (arr1[i] == 2.0 && arr2[i] == 1.0)
        {
            dSum[1][0]++;
        }
        
        else if (arr1[i] == 2.0 && arr2[i] == 2.0)
        {
            dSum[1][1]++;
        }
    }
    
    double dTotal = dSum[0][0] + dSum[0][1] + dSum[1][0] + dSum[1][1];
    double dRowSum[2] = {dSum[0][0] + dSum[0][1], dSum[1][0] + dSum[1][1]};
    
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (dSum[i][j] != 0)
            {
                dResult += -(dRowSum[i]/dTotal)*(dSum[i][j]/dRowSum[i])*log2(dSum[i][j]/dRowSum[i]);
            }
        }
    }
    
    return dResult;
}

//information gain을 구하는 function
double IG(double dEnt1, double dEnt2)
{
    return dEnt1-dEnt2;
}

//(Sorting 하지 않음) 한 attribute에 대한 column이 들어왔을 때, 그 column을 기준으로 모든 value의 IG을 구해서 IG이 가장 큰 것의 정보를 저장.
IG_Info MaxIG_Info(float fRorW[], float fAttr[], int nSize)
{
    float fMaxIG = 0;
    float fMaxIG_attr_value = 0;
    
    for (int i = 0; i < nSize; i++)
    {
        vector<float> vAttr_temp;
        vAttr_temp.resize(nSize);
        
        for (int j = 0; j < nSize; j++)
        {
            if (fAttr[i] > fAttr[j])
            {
                vAttr_temp[j] = 1;
            }
            else
            {
                vAttr_temp[j] = 2;
            }
        }
        
        double dCurrIG = IG(Entropy1(fRorW, nSize), Entropy2(vAttr_temp, fRorW, nSize));
        
        if(fMaxIG < dCurrIG)
        {
            fMaxIG = dCurrIG;
            fMaxIG_attr_value = fAttr[i];
        }
    }
    
    IG_Info ig;
    
    ig.dIG_value = fMaxIG;
    ig.fAttr_value = fMaxIG_attr_value;
    
    return ig;
}


