#include <iostream>
#include <opencv2/opencv.hpp>
#include "LBPCalculator.hpp"
#include <vector>
#include <time.h>

using namespace cv;
using namespace std;

int main(int argc, const char * argv[]) {
    Mat img = imread("/Users/HBSH/Desktop/LBP/LBP/batman.png", 0);
    LBPimageOut(img);
    MYimageOut(img);
    /*
     Mat* myWin =  makeWindows(LBPimageOut(img));
     
     //myWin에서 랜덤하게 세 개를 뽑아서 histogram을 그려주는 과정.
     srand(time(NULL));
     int randomNum[3] = {0};
     
     while (randomNum[0] == randomNum[1] || randomNum[0] == randomNum[2] || randomNum[1] == randomNum[2])
     {
     randomNum[0] = rand() % 16;
     randomNum[1] = rand() % 16;
     randomNum[2] = rand() % 16;
     }
     printf("====================================<<%d>>==========================================\n", randomNum[0]);
     makeHist(myWin[randomNum[0]]);
     printf("====================================<<%d>>==========================================\n", randomNum[1]);
     makeHist(myWin[randomNum[1]]);
     printf("====================================<<%d>>==========================================\n", randomNum[2]);
     makeHist(myWin[randomNum[2]]);
     */
    
    
    
    
    return 0;
}

