#include "csvTovector.hpp"
#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;

vector<vector<float> > ConvertToVector(char file1[], char file2[])
{
    vector<vector<float> > vWine;
    
    FILE * pFile1 = NULL;
    FILE * pFile2 = NULL;
    
    pFile1 = fopen(file1, "r");
    pFile2 = fopen(file2, "r");
    
    //csv 파일 읽어서 vWine에 저장
    //첫번째 column의 attr는 red인지 white인지 (red이면 1, white이면 2)
    if (pFile1 == NULL)
    {
        printf("파일이 존재하지 않습니다.");
    }
    
    else
    {
        while (1)
        {
            if (feof(pFile1))
            {
                break;
            }
            else
            {
                vector<float> vData;
                float fAttr = 0;
                vData.push_back(1);
                for (int i = 0; i < 11; i++)
                {
                    fscanf(pFile1, "%f,", &fAttr);
                    vData.push_back(fAttr);
                }
                fscanf(pFile1, "%f", &fAttr);
                vData.push_back(fAttr);
                vWine.push_back(vData);
            }
        }
    }
    
    if (pFile1 == NULL)
    {
        printf("파일이 존재하지 않습니다.");
    }
    
    else
    {
        while (1)
        {
            if (feof(pFile2))
            {
                break;
            }
            else
            {
                vector<float> vData;
                float fAttr = 0;
                vData.push_back(2);
                for (int i = 0; i < 11; i++)
                {
                    fscanf(pFile2, "%f,", &fAttr);
                    vData.push_back(fAttr);
                }
                fscanf(pFile2, "%f", &fAttr);
                vData.push_back(fAttr);
                vWine.push_back(vData);
            }
        }
    }
    
    fclose(pFile1);
    fclose(pFile2);
    
    return vWine;
}


