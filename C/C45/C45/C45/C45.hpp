#ifndef C45_hpp
#define C45_hpp

#include "IGCalculator.hpp"

#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>

using namespace std;

typedef struct Node
{
    vector<vector<float>> vWine;
    int nAttr; //몇번째 attribute인지 저장.
    float fAttribute_value;
    int nNumOfRed; //red wine의 갯수 저장.
    int nNumOfWhite; //white wine의 갯수 저장.
    float fProbablityOfRed; //red일 확률 저장.
    float fProbablityOfWhite; //white일 확률 저장.
    
    int nOutcome; //red 갯수가 많으면 1, white 갯수가 많으면 2 저장.
    
    struct Node *pLeft;
    struct Node *pRight;
}Node;

Node* c45(vector<vector<float>> vWine);

void initNode(Node* pNode);

#endif /* C45_hpp */

