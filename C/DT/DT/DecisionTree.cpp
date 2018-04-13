//using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>

#define buf 128
int live[6]={1,1,1,1,1,1}; // 0~5 중에 걸러지지 않은 것은 1, 걸러진 것은 0

typedef struct _Person
{
    int survived;//0
    int pclass;//1
    int sibsp;//2
    int parch;//3
    int embarked;//4
    int sex;//5
} Person;

typedef struct _NODE
{
    //int nAttr;
    //vector<Node* > vChild;
    //vector<int> vData;
    int nodeNum;//[pclass이면 1, sibsp이면 2, parch이면 3, embarked이면 4, sex이면 5]
    struct _NODE *child[5];
}Node;

//한가지에 대해서만 엔트로피를 구할 때 사용하는 function
double Entropy1(int arr[])
{
    int num[5]={0};
    double result=0;
    for(int i=0; i<891; i++)
    {
        for(int j=0; j<4; j++)
        {
            if(arr[i]!=0)
            {
                if(arr[i]==j)
                {
                    num[j]++;
                    //printf("num[%d]: %d\n", j,num[j]);
                }
                else if(arr[i]>3)
                {
                    num[4]++;
                }
            }
        }
    }
    
    for(int i=0; i<5; i++)
    {
        if(num[i]!=0)
        {
            result+=-((double)num[i]/891)*log2((double)num[i]/891);
            //printf("num[%d]: %d\n",i, num[i]);
        }
    }
    return result;
}
//두가지 요소 간에 엔트로피를 구할 때 사용하는 function
double Entropy2(int arr1[], int arr2[])
{
    int array[5][5]={0};
    int sum=0;
    int rsum[5]={0};
    double result=0;
    
    for(int i=0; i<891; i++)
    {
        
        for(int a=0; a<5; a++)
        {
            for(int b=0; b<5; b++)
            {
                if((arr2[i]!=0)&&(arr1[i]!=0))
                {
                    if((arr2[i]==a)&&(arr1[i]==b))
                    {
                        array[a][b]++;
                    }
                }
            }
        }
    }
    
    
    for(int i=0; i<5; i++)
    {
        for(int j=0; j<5; j++)
        {
            sum+=array[i][j];
            rsum[i]+=array[i][j];
            //printf("%5d", array[i][j]);
        }
        //printf("\n");
    }
    
    for(int i=0; i<5; i++)
    {
        double ent=0;
        for(int j=0; j<5; j++)
        {
            if(rsum[i]!=0)
            {
                if(array[i][j]!=0)
                {
                    ent+=-(double)array[i][j]/rsum[i]*log2((double)array[i][j]/rsum[i]);
                    
                }
            }
            
        }
        result+=(double)rsum[i]/sum*ent;
    }
    return result;
}

//information gain을 구하는 function
double IG(double ent1, double ent2)
{
    return ent1-ent2;
}

//실제로 ID3를 실행하는 function.
Node* ID3(int person[6][891])
{
    //survived: 0
    //pclass: 1
    //sibsp: 2
    //parch: 3
    //embarked: 4
    //sex: 5
    
    struct _NODE *node = new _NODE;//동적할당
    double infoGain[6] = {0};
    double max = 0; //IG의 최댓값 저장
    int maxNum = 0; //[pclass: 1, sibsp: 2, parch: 3, embarked: 4, sex: 5] 중 IG이 가장 큰 것의 숫자를 maxNum에 저장(pclass가 가장 크다면 maxNum==1).
    int personNew1[6][891] = {0};
    int personNew2[6][891] = {0};
    int personNew3[6][891] = {0};
    int personNew4[6][891] = {0};
    int personNum[5] = {0}; //예를 들어 pclass이면 1, 2, 3이 있는데 이때 personNum[1], personNum[2], personNum[3]는 1, 나머지는 0
    
    
    
    int Alive = 0;
    int Death = 0;
    
    int accum=0;
    for (int j = 0; j < 891; j++)
    {
        accum+=person[0][j];
    }
    
    
    //IG가 가장 큰 것 찾음
    for (int i = 1; i < 6; i++)
    {
        if (live[i] == 1 && accum != 0)
        {
            /*
             for(int i=0; i<6; i++)
             {
             for(int j=0; j<891; j++)
             {
             printf("%2d",person[i][j]);
             }
             printf("\n\n");
             }
             */
            //printf("Entropy1(person[0]): %lf\n",Entropy1(person[0]));
            //printf("Entropy2(person[0], person[%d]): %lf\n\n",i,Entropy2(person[0], person[i]));
            infoGain[i]=IG(Entropy1(person[0]),Entropy2(person[0], person[i]));
            
            printf("infoGain[%d]: %lf\n\n",i,infoGain[i]);
        }
    }
    
    max = infoGain[0];
    for (int i = 1; i < 6; i++)
    {
        if (max < infoGain[i])
        {
            max = infoGain[i];
            maxNum = i;
        }
    }
    if(maxNum == 0){
        
        for (int j = 0; j < 891; j++)
        {
            if (person[0][j] == 1)
            {
                Alive++;
            }
            else if (person[0][j] == 2)
            {
                Death++;
            }
        }
        
        printf("Alive: %d\n", Alive);
        printf("Death: %d\n", Death);
        
        return node;
    }
    else{
        node->nodeNum=maxNum;
        
        //attribute마다 1,2,3,4가 있는지 찾고 1,2,3,4 각각마다 personNew를 나눈다.
        
        for (int j = 0; j < 891; j++)
        {
            //personNew1을 새로 만든다. 이때 maxNum row에 1이 있는 person의 column만 personNew1에 저장한다. 이후에 personNum[1]에 1을 대입시켜 1이 있다는 정보를 저장한다.
            if (person[maxNum][j] == 1)
            {
                for (int i = 0; i < 6; i++)
                {
                    personNew1[i][j] = person[i][j];
                }
                for (int i = 0; i < 891; i++)
                {
                    personNew1[maxNum][i]=0;
                }
                personNum[1] = 1;
            }//personNew2을 새로 만든다. 이때 maxNum row에 2가 있는 person의 column만 personNew2에 저장한다. 이후에 personNum[2]에 1을 대입시켜 2가 있다는 정보를 저장한다.
            else if (person[maxNum][j] == 2)
            {
                for (int i = 0; i < 6; i++)
                {
                    personNew2[i][j] = person[i][j];
                }
                for (int i = 0; i < 891; i++)
                {
                    personNew2[maxNum][i]=0;
                }
                personNum[2] = 1;
            }//personNew3을 새로 만든다. 이때 maxNum row에 3이 있는 person의 column만 personNew3에 저장한다. 이후에 personNum[3]에 1을 대입시켜 3이 있다는 정보를 저장한다.
            else if (person[maxNum][j] == 3)
            {
                for (int i = 0; i < 6; i++)
                {
                    personNew3[i][j] = person[i][j];
                }
                for (int i = 0; i < 891; i++)
                {
                    personNew3[maxNum][i]=0;
                }
                personNum[3] = 1;
            }//personNew4을 새로 만든다. 이때 maxNum row에 4가 있는 person의 column만 personNew4에 저장한다. 이후에 personNum[4]에 1을 대입시켜 4가 있다는 정보를 저장한다.
            else if (person[maxNum][j] == 4)
            {
                for (int i = 0; i < 6; i++)
                {
                    personNew4[i][j] = person[i][j];
                }
                for (int i = 0; i < 891; i++)
                {
                    personNew4[maxNum][i]=0;
                }
                personNum[4] = 1;
            }
        }
        
        
        //maxNum에 해당하는 row의 모든 값을 0으로 바꿔준다.
        for (int i = 0; i < 891; i++)
        {
            personNew1[maxNum][i]=0;
            personNew2[maxNum][i]=0;
            personNew3[maxNum][i]=0;
            personNew4[maxNum][i]=0;
        }
        /*
         printf("---------------------------------------------------------------------\n");
         printf("[personNew1]\n");
         
         for(int i=0; i<6; i++)
         {
         for(int j=0; j<891; j++)
         {
         printf("%2d",personNew1[i][j]);
         }
         printf("\n");
         }
         printf("---------------------------------------------------------------------\n");
         printf("[personNew2]\n");
         for(int i=0; i<6; i++)
         {
         for(int j=0; j<891; j++)
         {
         printf("%2d",personNew2[i][j]);
         }
         printf("\n");
         }
         printf("---------------------------------------------------------------------\n");
         printf("[personNew3]\n");
         for(int i=0; i<6; i++)
         {
         for(int j=0; j<891; j++)
         {
         printf("%2d",personNew3[i][j]);
         }
         printf("\n");
         }
         printf("---------------------------------------------------------------------\n");
         printf("[personNew4]\n");
         for(int i=0; i<6; i++)
         {
         for(int j=0; j<891; j++)
         {
         printf("%2d",personNew4[i][j]);
         }
         printf("\n");
         }
         printf("---------------------------------------------------------------------\n");
         */
        printf("maxNum: %d\n",maxNum);
        printf("IG: %lf\n",max);
        printf("====================================================================\n\n");
        
        live[maxNum] = 0;
        
        int surv = 0;
        int notsurv = 0;
        
        for (int i = 0; i < 891; i++)
        {
            if (person[0][i] == 1)
            {
                surv++;
            }
            else if (person[0][i] == 2)
            {
                notsurv++;
            }
        }
        
        int liveSum = 0;
        for (int i = 0; i < 6; i++)
        {
            liveSum+=live[i];
        }
        
        int acc1 = 0;
        int acc2 = 0;
        int acc3 = 0;
        int acc4 = 0;
        
        for (int j = 0; j < 891; j++)
        {
            acc1 += personNew1[0][j];
            acc2 += personNew2[0][j];
            acc3 += personNew3[0][j];
            acc4 += personNew4[0][j];
            
        }
        
        
        
        
        if (surv == 0 || notsurv == 0||liveSum == 0)
        {
            
            printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
            return node;//마지막 child node를 return
        }
        
        
        else
        {
            if (acc1 != 0 && personNum[1] == 1)
            {
                printf("child[1]으로 감\n");
                node -> child[1] = ID3(personNew1);
            }
            if (acc2 != 0 && personNum[2] == 1)
            {
                printf("child[2]으로 감\n");
                node -> child[2] = ID3(personNew2);
            }
            if(acc3 != 0 && personNum[3]==1)
            {
                printf("child[3]으로 감\n");
                node -> child[3] = ID3(personNew3);
            }
            if (acc4 != 0 && personNum[4]==1)
            {
                printf("child[4]으로 감\n");
                node -> child[4] = ID3(personNew4);
            }
            return node;
        }
    }
}
int main(void)
{
    
    Person p[891];
    char str[buf];
    int su[891];
    int pc[891];
    int si[891];
    int pa[891];
    int em[891];
    int se[891];
    int person[6][891];
    
    //각각의 attribute를 따로 따로 txt파일로 받아서 각각의 배열에 저장.
    //이후에 person이라는 2차원 배열에 모든 attribute를 저장.
    FILE *fp1=fopen("/Users/gehunhangbo/Desktop/DecisionTree/DecisionTree/embarked.txt", "r");
    FILE *fp2=fopen("/Users/gehunhangbo/Desktop/DecisionTree/DecisionTree/parch.txt", "r");
    FILE *fp3=fopen("/Users/gehunhangbo/Desktop/DecisionTree/DecisionTree/pclass.txt", "r");
    FILE *fp4=fopen("/Users/gehunhangbo/Desktop/DecisionTree/DecisionTree/sex.txt", "r");
    FILE *fp5=fopen("/Users/gehunhangbo/Desktop/DecisionTree/DecisionTree/sibsp.txt", "r");
    FILE *fp6=fopen("/Users/gehunhangbo/Desktop/DecisionTree/DecisionTree/survived.txt", "r");
    
    if(fp1==NULL||fp2==NULL||fp3==NULL||fp4==NULL||fp5==NULL||fp6==NULL)
    {
        puts("File is not available.");
        return -1;
    }
    
    for(int i=0; i<891; i++)
    {
        fgets(str,buf,fp6);
        p[i].survived=atoi(str)+1;
        su[i]=p[i].survived;
        //printf("survived[%d]: %d\n",i, su[i]);
        
        fgets(str,buf,fp3);
        p[i].pclass=atoi(str)+1;
        pc[i]=p[i].pclass;
        //printf("pclass[%d]: %d\n",i, p[i].pclass);
        
        fgets(str,buf,fp5);
        p[i].sibsp=atoi(str)+1;
        si[i]=p[i].sibsp;
        //printf("sibsp[%d]: %d\n",i,p[i].sibsp);
        
        fgets(str,buf,fp2);
        p[i].parch=atoi(str)+1;
        pa[i]=p[i].parch;
        //printf("parch[%d]: %d\n",i,p[i].parch);
        
        fgets(str,buf,fp1);
        if(*str=='Q')
        {
            p[i].embarked=1;
            em[i]=1;
        }
        else if(*str=='S')
        {
            p[i].embarked=2;
            em[i]=2;
        }
        else
        {
            p[i].embarked=3;
            em[i]=3;
        }
        //printf("embarked[%d]: %d\n",i,p[i].embarked);
        
        fgets(str,buf,fp4);
        p[i].sex=atoi(str)+1;
        se[i]=p[i].sex;
        //printf("sex[%d]: %d\n",i,p[i].sex);
        
        //printf("\n");
    }
    
    // person이라는 배열에 한번에 저장.
    for(int i=0; i<891; i++)
    {
        person[0][i]=su[i];
        person[1][i]=pc[i];
        person[2][i]=si[i];
        person[3][i]=pa[i];
        person[4][i]=em[i];
        person[5][i]=se[i];
    }
    
    int sum=0;
    for(int i=0; i<891; i++)
    {
        sum+=su[i];
    }
    /*
     printf("Entropy1(su): %lf\n",Entropy1(su));
     printf("Entropy2(su,se): %lf\n",Entropy2(su, se));
     printf("Entropy2(su,pc): %lf\n",Entropy2(su, pc));
     printf("Entropy1(su,si): %lf\n",Entropy2(su, si));
     printf("Entropy1(su,em): %lf\n",Entropy2(su, em));
     */
    
    ID3(person);
    /*
    int A[6][891] = {0};
    for(int i=0; i<6; i++)
    {
        for(int j=0; j<891; j++)
        {
            A[i][j]=person[i][j];
        }
    }
    
    
    for(int j=0; j<891; j++)
    {
        if(person[1][j] != 3)
        {
            A[0][j] = 0;
        }
        
        if(person[2][j]==4)
        {
            A[0][j] = 0;
        }
        
        if(person[3][j]==1)
        {
            A[0][j] = 0;
        }
        
        
        if(person[4][j]==2)
        {
            A[0][j] = 0;
        }
        
        if(person[5][j]==1)
        {
            A[0][j] = 0;
        }
    }
    
    for (int i = 0; i < 891; i++)
    {
        printf("%d ", person[0][i]);
    }
    */
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);
    fclose(fp5);
    fclose(fp6);
    
    return 0;
}

