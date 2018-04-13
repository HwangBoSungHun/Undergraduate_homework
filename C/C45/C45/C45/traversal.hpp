#ifndef traversal_hpp
#define traversal_hpp

#include "C45.hpp"
#include <stdio.h>
#include <vector>

using namespace std;

//preorder traversal 이용해서 tree 확인.
void preorder_traversal(Node* pRoot);

//data set으로 들어간 wine을 분석하여 red 와인인지 white 와인인지 예측하고, 실제 값(실제로 red 와인인지 white인지)과 비교하여 accuracy를 return 함.
int accuracyCalc(Node* pRoot, vector<vector<float> > vWine);

#endif /* traversal_hpp */

