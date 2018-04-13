#include "LBPCalculator.hpp"

#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;
using namespace std;

//이미지 받아들여 LBP를 계산해서 vector<int > 형태로 반환.
vector<int > LBPCal(Mat img)
{
    int r = img.rows;
    int c = img.cols;
    
    vector<int > vAfterLBP;
    
    for (int y = 1; y < c-1; y++)
    {
        for (int x = 1; x < r-1; x++)
        {
            int nCurrent = img.at<uchar>(y, x);
            int nSum = 0;
            
            if (img.at<uchar>(y-1, x-1) >= nCurrent)
            {
                nSum += 128;
            }
            if (img.at<uchar>(y-1, x) >= nCurrent)
            {
                nSum += 64;
            }
            if (img.at<uchar>(y-1, x+1) >= nCurrent)
            {
                nSum += 32;
            }
            if (img.at<uchar>(y, x-1) >= nCurrent)
            {
                nSum += 16;
            }
            if (img.at<uchar>(y, x+1) >= nCurrent)
            {
                nSum += 8;
            }
            if (img.at<uchar>(y+1, x-1) >= nCurrent)
            {
                nSum += 4;
            }
            if (img.at<uchar>(y+1, x) >= nCurrent)
            {
                nSum += 2;
            }
            if (img.at<uchar>(y+1, x+1) >= nCurrent)
            {
                nSum += 1;
            }
            
            vAfterLBP.push_back(nSum);
        }
    }
    return vAfterLBP;
}


vector<int > MYCal(Mat img)
{
    int r = img.rows;
    int c = img.cols;
    
    vector<int > vAfterLBP;
    
    for (int y = 1; y < r-1; y++)
    {
        for (int x = 1; x < c-1; x++)
        {
            int nCurrent = img.at<uchar>(y, x);
            int nSum = 0;
            
            nSum += abs(img.at<uchar>(y-1, x-1) - nCurrent);
            nSum += abs(img.at<uchar>(y-1, x) - nCurrent);
            nSum += abs(img.at<uchar>(y-1, x+1) - nCurrent);
            nSum += abs(img.at<uchar>(y, x-1) - nCurrent);
            nSum += abs(img.at<uchar>(y, x+1) - nCurrent);
            nSum += abs(img.at<uchar>(y+1, x-1) - nCurrent);
            nSum += abs(img.at<uchar>(y+1, x) - nCurrent);
            nSum += abs(img.at<uchar>(y+1, x+1) - nCurrent);
            
            vAfterLBP.push_back(nSum);
        }
    }
    
    return vAfterLBP;
}

//LBP 과정을 거친 이미지를 받아들여 png 파일로 저장 및 Mat형으로 반환.
Mat LBPimageOut(Mat img)
{
    vector<int > vNewImg = LBPCal(img);
    int r = img.rows - 2;
    int c = img.cols - 2;
    Mat newImg(r, c, CV_8UC1);
    
    for (int y = 0; y < c; y++)
    {
        for(int x = 0; x < r; x++)
        {
            newImg.at<uchar>(y, x) = vNewImg[y * r + x];
        }
    }
    
    imwrite("/Users/HBSH/Desktop/LBP/LBP/test.png", newImg);
    return newImg;
}

Mat MYimageOut(Mat img)
{
    vector<int > vNewImg = MYCal(img);
    int r = img.rows - 2;
    int c = img.cols - 2;
    Mat newImg(r, c, CV_8UC1);
    
    for (int y = 0; y < r; y++)
    {
        for(int x = 0; x < c; x++)
        {
            newImg.at<uchar>(y, x) = vNewImg[y * r + x];
        }
    }
    
    imwrite("/Users/HBSH/Desktop/LBP/LBP/test_my.png", newImg);
    return newImg;
}
//이미지를 받아들여 4X4로 분할 후 Mat*형으로 반환.
Mat* makeWindows(Mat img)
{
    Mat * pImgWins = new Mat[16];
    
    int r = img.rows;
    int c = img.cols;
    
    for (int i = 0; i < 16; i++)
    {
        pImgWins[i] = Mat(r/4, c/4, CV_8UC1);
    }
    
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            for (int y = (r/4) * i; y < (r/4) * (i+1); y++)
            {
                for (int x = (c/4) * j; x < (c/4) * (j+1); x++)
                {
                    pImgWins[i*4 + j].at<uchar>(y - (r/4)*i, x - (c/4)*j) = img.at<uchar>(y, x);
                }
            }
        }
    }
    return pImgWins;
}

//하나의 window에 0~256까지의 수가 각각 몇 개 있는지 histogram 출력 및 int*형으로 반환.
int* makeHist(Mat img)
{
    int r = img.rows;
    int c = img.cols;
    int* pHist = new int[256];
    for (int i = 0; i < 256; i++)
    {
        pHist[i] = 0;
    }
    
    
    for (int y = 0; y < r; y++)
    {
        for (int x = 0; x < c; x++)
        {
            for (int i = 0; i < 256; i++)
            {
                if (img.at<uchar>(y, x) == i)
                {
                    pHist[i]++;
                }
            }
        }
    }
    
    for (int i = 0; i < 256; i++)
    {
        printf("hist[%3d]: ", i);
        for (int j = 0; j <  pHist[i]; j++)
        {
            printf("I");
        }
        printf("\n");
    }
    
    
    return pHist;
}







