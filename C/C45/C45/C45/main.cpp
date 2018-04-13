#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>

#include "C45.hpp"
#include "csvTovector.hpp"
#include "IGCalculator.hpp"
#include "traversal.hpp"

using namespace std;


int main(int argc, const char * argv[]) {
    
    vector<vector<float> > vWine;
    char red[] = "/Users/HBSH/Desktop/STUDY/ICU/C45/C45/C45/red_train.csv";
    char white[] = "/Users/HBSH/Desktop/STUDY/ICU/C45/C45/C45/white_train.csv";
    
    vWine = ConvertToVector(red, white);
    
    Node * pRoot = c45(vWine);
    
    preorder_traversal(pRoot);
    
    vector<vector<float>> vWine_test;
    char red_test[] = "/Users/HBSH/Desktop/STUDY/ICU/C45/C45/C45/red_test.csv";
    char white_test[] = "/Users/HBSH/Desktop/STUDY/ICU/C45/C45/C45/white_test.csv";
    
    vWine_test = ConvertToVector(red_test, white_test);
    
    int nResult = accuracyCalc(pRoot, vWine_test);
    
    printf("------------<TEST>------------\n");
    printf("Number of test set: %d\n", (int)vWine_test.size());
    printf("Correct number of test set: %d\n", nResult);
    printf("Accuracy: %.1f%%\n", (float)nResult/vWine_test.size()*100);
    printf("------------------------------\n");
    
    return 0;
}

