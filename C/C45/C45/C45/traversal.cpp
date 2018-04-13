#include "traversal.hpp"
#include "C45.hpp"
#include <stdio.h>
#include <vector>

using namespace std;

const int Red = 1;
const int White = 2;

void preorder_traversal(Node * pRoot)
{
    printf("-----[Preorder Traversal]-----\n\n");
    
    if ((pRoot -> pLeft == NULL) && (pRoot -> pRight == NULL))
    {
        printf("[pLeft == NULL] && [pRight == NULL]\n");
        printf("Number of red wine: %d\n", pRoot -> nNumOfRed);
        printf("Number of white wine: %d\n", pRoot -> nNumOfWhite);
        printf("Probability of red wine: %.2f\n", pRoot -> fProbablityOfRed);
        printf("Probability of white wine: %.2f\n", pRoot -> fProbablityOfWhite);
        printf("            [END]\n------------------------------\n");
    }
    
    else
    {
        printf("[pLeft != NULL] && [pRight != NULL]\n");
        printf("Attribute: %d\n", pRoot -> nAttr);
        printf("Attribute value: %f\n", pRoot -> fAttribute_value);
        printf("Number of red wine: %d\n", pRoot -> nNumOfRed);
        printf("Number of white wine: %d\n", pRoot -> nNumOfWhite);
        printf("Probability of red wine: %.2f\n", pRoot -> fProbablityOfRed);
        printf("Probability of white wine: %.2f\n", pRoot -> fProbablityOfWhite);
        printf("------------------------------\n\n");
        
        preorder_traversal(pRoot -> pLeft);
        preorder_traversal(pRoot -> pRight);
    }
}

int accuracyCalc(Node * pRoot, vector<vector<float> > vWine)
{
    int nCorrectNum = 0;
    
    if ((pRoot -> pLeft == NULL) && (pRoot -> pRight == NULL))
    {
        float* fRorW = new float[vWine.size()];
        int nNumOfRed = 0;
        int nNumOfWhite = 0;
        
        for (int i = 0; i < vWine.size(); i++)
        {
            fRorW[i] = (pRoot -> vWine[i][0]);
            if (fRorW[i] == Red)
            {
                nNumOfRed++;
            }
            else if (fRorW[i] == White)
            {
                nNumOfWhite++;
            }
        }
        
        if (pRoot -> nOutcome == Red)
        {
            nCorrectNum += nNumOfRed;
        }
        else
        {
            nCorrectNum += nNumOfWhite;
        }
    }
    
    else
    {
        vector<vector<float> > vLeft;
        vector<vector<float> > vRight;
        
        for (int i = 0; i < vWine.size(); i++)
        {
            if (vWine[i][pRoot -> nAttr] < pRoot -> fAttribute_value)
            {
                vLeft.push_back(vWine[i]);
            }
            else
            {
                vRight.push_back(vWine[i]);
            }
        }
        
        pRoot -> pLeft -> vWine = vLeft;
        pRoot -> pRight -> vWine = vRight;
        
        nCorrectNum += accuracyCalc(pRoot -> pLeft, pRoot -> pLeft -> vWine);
        nCorrectNum += accuracyCalc(pRoot -> pRight, pRoot -> pRight -> vWine);
    }
    
    return nCorrectNum;
}

