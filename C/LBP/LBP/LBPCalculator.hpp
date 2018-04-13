#ifndef LBPCalculator_hpp
#define LBPCalculator_hpp

#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>


using namespace cv;
using namespace std;

vector<int > LBPCal(Mat img); //이미지 받아들여 LBP를 계산해서 vector<int > 형태로 반환.
Mat LBPimageOut(Mat img); //LBP 과정을 거친 이미지를 받아들여 png 파일로 저장 및 Mat형으로 반환.
vector<int > MYCal(Mat img);
Mat MYimageOut(Mat img);
Mat* makeWindows(Mat img); //이미지를 받아들여 4X4로 분할 후 Mat*형으로 반환.
int* makeHist(Mat img);//하나의 window에 0~256까지의 수가 각각 몇 개 있는지 histogram 출력 및 int*형으로 반환.

#endif /* LBPCalculator_hpp */


