#include "C45.hpp"
#include "IGCalculator.hpp"

#include <iostream>
#include <vector>
#include <stdio.h>

using namespace std;

const int Red = 1;
const int White = 2;
const int NumOfAttr = 13;

void initNode(Node* pNode)
{
    pNode -> nAttr = 0; //몇번째 attribute인지 저장.
    pNode -> fAttribute_value = 0.0f;
    pNode -> nNumOfRed = 0; //red wine의 갯수 저장.
    pNode -> nNumOfWhite = 0; //white wine의 갯수 저장.
    pNode -> fProbablityOfRed = 0.0f; //red일 확률 저장.
    pNode -> fProbablityOfWhite = 0.0f; //white일 확률 저장.
    
    pNode -> pLeft = NULL;
    pNode -> pRight = NULL;
}

Node* c45(vector<vector<float> > vWine)
{
    vector<Node*> vStack; //vStack에 node 저장.
    
    Node* pRoot = new Node;
    initNode(pRoot);
    
    int numOfNode = 0;
    
    pRoot -> vWine = vWine;
    vStack.push_back(pRoot); //pRoot node를 vStack에 저장.
    
    //vStack에 저장된 node가 하나도 없을 때까지 반복.
    while (!vStack.empty())
    {
        Node* pCurrentNode = vStack.back(); //pCurrentNode는 vStack에 저장된 node 중 가장 마지막에 push 된 것.
        vStack.pop_back(); //마지막 node 제거.
        
        int nWineSize = (int)(pCurrentNode -> vWine.size()); //wine이 총 몇 병인지 저장.
        float *fRorW = new float[nWineSize]; //각각의 wine이 red인지 white인지 저장. (red이면 1, white이면 2)
        float *fAttr = new float[nWineSize]; //나중에 하나의 attribute에 대한 값을 attr[]에 저장. 즉 한 attribute에 대응하는 column을 저장.
        
        //vWine[][0]을 통해 red인지 white인지 확인하고 RorW[]에 저장.
        for (int i = 0; i < nWineSize; i++)
        {
            fRorW[i] = (pCurrentNode -> vWine[i][0]);
            if (fRorW[i] == Red)
            {
                pCurrentNode -> nNumOfRed++;
            }
            else if (fRorW[i] == White)
            {
                pCurrentNode -> nNumOfWhite++;
            }
        }
        //red 갯수가 많으면 1, white 갯수가 많으면 2 저장.
        if (pCurrentNode -> nNumOfRed > pCurrentNode -> nNumOfWhite)
        {
            pCurrentNode -> nOutcome = Red;
        }
        else
        {
            pCurrentNode -> nOutcome = White;
        }
        
        //확률 계산.
        pCurrentNode -> fProbablityOfRed = (pCurrentNode-> nNumOfRed) / ((float)(pCurrentNode -> nNumOfRed) + (pCurrentNode -> nNumOfWhite));
        pCurrentNode -> fProbablityOfWhite = (pCurrentNode-> nNumOfWhite) / ((float)(pCurrentNode -> nNumOfRed) + (pCurrentNode -> nNumOfWhite));
        
        //종료 조건.
        if ((pCurrentNode -> fProbablityOfRed > 0.95) || (pCurrentNode -> fProbablityOfWhite > 0.95)|| (pCurrentNode -> nNumOfRed < 20) || (pCurrentNode -> nNumOfWhite < 20))
        {
            numOfNode++;
            printf("[종료] %d번째\n", numOfNode);
            printf("Number of red wine: %d\n", pCurrentNode -> nNumOfRed);
            printf("Number of white wine: %d\n", pCurrentNode -> nNumOfWhite);
            printf("Probability of red wine: %f\n", pCurrentNode -> fProbablityOfRed);
            printf("Probability of white wine: %f\n", pCurrentNode -> fProbablityOfWhite);
            
            if (pCurrentNode -> nOutcome == Red)
            {
                printf("<<<<<RED!>>>>>\n\n");
            }
            else
            {
                printf("<<<<<WHITE!>>>>>\n\n");
            }
        }
        
        //종료 조건이 아닐 때
        else
        {
            double dMaxIG = 0;
            int nMaxIG_col_idx = 0;
            float fAttr_value = 0;
            
            //어떤 attribute의 IG이 가장 큰 지 알아보기 위한 과정.
            for (int i = 1; i < NumOfAttr; i++)
            {
                for (int j = 0; j < nWineSize; j++)
                {
                    fAttr[j] = pCurrentNode -> vWine[j][i];
                }
                
                //각각의 attribute마다 IG이 가장 큰 것의 index와 IG 값, 해당 index에서의 attribute 값을 MaxIG_Info를 이용해서 구한다.
                IG_Info ig = MaxIG_Info(fRorW, fAttr, nWineSize);
                
                //모든 attribute 중에서 IG이 가장 큰 것의 index와 IG 값, 해당 index에서의 attribute 값을 변수에 저장한다.
                if (dMaxIG < ig.dIG_value)
                {
                    dMaxIG = ig.dIG_value;
                    nMaxIG_col_idx = i;
                    fAttr_value = ig.fAttr_value;
                }
            }
            
            //nAttr에는 attribute 중 IG이 가장 큰 것의 attribute를 저장.
            pCurrentNode -> nAttr = nMaxIG_col_idx;
            pCurrentNode -> fAttribute_value = fAttr_value;
            
            //위에서 IG이 가장 큰 attribute와 그 attribute에서의 index를 구했으므로 그 정보를 이용해서 child node인 left와 right로 나눈다.
            Node* leftChild = new Node;
            Node* rightChild = new Node;
            
            initNode(leftChild);
            initNode(rightChild);
            
            for (int i = 0; i < nWineSize; i++)
            {
                if (pCurrentNode -> vWine[i][nMaxIG_col_idx] < fAttr_value)
                {
                    leftChild -> vWine.push_back(pCurrentNode -> vWine[i]);
                }
                else
                {
                    rightChild -> vWine.push_back(pCurrentNode -> vWine[i]);
                }
            }
            
            pCurrentNode -> pLeft = leftChild;
            pCurrentNode -> pRight = rightChild;
            
            vStack.push_back(pCurrentNode -> pLeft); // vStack에 pCurrentNode의 left node 저장.
            vStack.push_back(pCurrentNode -> pRight); // vStack에 pCurrentNode의 right node 저장.
        }
        delete[] fRorW;
        delete[] fAttr;
    }
    return pRoot;
}

