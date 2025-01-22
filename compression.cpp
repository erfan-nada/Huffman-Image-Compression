
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class CTreeNode
{
    public:
    int info;
    char character[1000];
    CTreeNode * pRight;
    CTreeNode * pLeft;
};
class CSNode
{
    public:
    CSNode * pNext;
    CTreeNode * pDown;
    int info;
    char character[1000];
};
class CNode
{
    public:
    char character;
    char bits[100];
    CNode*pnext;
};
class CTree
{
    public:
    CTreeNode* pRoot;
    CTree()
    {
        pRoot=NULL;
    }
};
class CSList
{
public:
    CSNode* pHead;
    CSList()
    {
        pHead = NULL;
    }
    ~CSList()
    {
        CSNode* pTrav = pHead;
        while (pHead != NULL)
        {
            pHead = pTrav->pNext;
            pTrav->pNext = NULL;
            delete pTrav;
            pTrav = pHead;
        }
    }

    void insert(CSNode* pnn)
    {
        if (pHead == NULL)
        {
            pHead = pnn;
        }
        else
        {
            CSNode* pB = NULL;
            CSNode* pTrav = pHead;
            while (pTrav != NULL && pTrav->info < pnn->info)
            {
                pB = pTrav;
                pTrav = pTrav->pNext;
            }
            if (pB != NULL)
            {
                pB->pNext = pnn;
                pnn->pNext = pTrav;
            }
            else
            {
                pHead = pnn;
                pnn->pNext = pTrav;
            }
        }
    }

    CSNode* remove()
    {
        if (pHead == NULL)
        {
            return NULL;
        }
        else
        {
            CSNode* pTrav = pHead;
            pHead = pHead->pNext;
            pTrav->pNext = NULL;
            return pTrav;
        }
    }
};
class CList
{
    public:
    CNode*pHead;
    CNode*pTail;

    CList()
    {
        
        pHead=NULL;
        pTail=NULL;
    }
    ~CList()
    {
        CNode*pTrav=pHead;
        while(pHead!=NULL)
        {
            pHead=pTrav->pnext;
            pTrav->pnext=NULL;
            delete pTrav;
            pTrav=pHead;

        }
    }
    void Attach(CNode*pnn)
    {
        if(pHead==NULL)
        {
            pHead=pnn;
            pTail=pnn;
        }
        else
        {
            pTail->pnext=pnn;
            pTail=pnn;
        }
    }
    
};
void traverseLeaves(CTreeNode* pRoot, char* Bits, int len) 
{
    if (pRoot == NULL)
        return;

    if (pRoot->pLeft == NULL && pRoot->pRight == NULL) 
    {
        Bits[len] = '\0';  
        cout << pRoot->character << " >> " << Bits << endl;
    }

    if (pRoot->pLeft != NULL) 
    {
        Bits[len] = '0';    
        traverseLeaves(pRoot->pLeft, Bits, len + 1);  
    }

    if (pRoot->pRight != NULL) 
    {
        Bits[len] = '1';     
        traverseLeaves(pRoot->pRight, Bits, len + 1);  
    }
}
CNode* makeClist(CTreeNode* pRoot, char* Bits, int len, CList & List) 
{
    if (pRoot == NULL)
        return List.pHead;  

    if (pRoot->pLeft == NULL && pRoot->pRight == NULL) 
    {
        Bits[len] = '\0';  
        CNode* pnn = new CNode;
        pnn->character = pRoot->character[0];  
        int i = 0;
        for (; Bits[i]!='\0'; i++) 
        {
            pnn->bits[i] = Bits[i];
        }
        pnn->bits[i] = '\0'; 
        pnn->pnext = NULL; 
        List.Attach(pnn); 
    }

    if (pRoot->pLeft != NULL) 
    {
        Bits[len] = '0';
        CNode*pTemp = makeClist(pRoot->pLeft, Bits,len+1, List); 
    }

    if (pRoot->pRight != NULL) 
    {
        Bits[len] = '1';     
        CNode* pTemp = makeClist(pRoot->pRight, Bits,len+1, List);  
    }

    return List.pHead;  
}

int main()
{
    ifstream fl("C:\\Users\\erfan\\Desktop\\Huffman Tree-Project\\1.bmp", ifstream::binary);
    ofstream fl2("C:\\Users\\erfan\\Desktop\\Huffman Tree-Project\\encoded.bmp", ofstream::binary);   
    ofstream fl3("C:\\Users\\erfan\\Desktop\\Huffman Tree-Project\\Huffman_Code.bmp", ofstream::binary);   

    char* bmpHeader= new char [54];
    fl.read(bmpHeader, 54);
    fl2.write(bmpHeader, 54);

    
    fl.seekg(54, fl.end);
    int h=fl.tellg();
    cout<<h<<endl;
    fl.seekg(54, fl.beg);
    char ch;

    char Ltrs[256]; 
    int ct[256]={0};
    int uniqueCount = 0;
    for(int i=0;i<h;i++)
    {
        fl.read(&ch,1);
        char currentChar = ch;

        int found = 0;
        for (int j = 0; j < uniqueCount; j++) 
        {
            if (Ltrs[j] == currentChar) 
            {
                ct[j]++;
                found = 1;
                break;
            }
        }

        if (found==0) 
        {
            Ltrs[uniqueCount] = currentChar;
            ct[uniqueCount] = 1;
            uniqueCount++;
        }
    }
    cout << "Character Count:" << endl;
    for (int i = 0; i < uniqueCount; i++) 
    {
        cout << Ltrs[i] << ": " << ct[i] << endl;
    }
    cout<<endl<<endl;
    
    CSNode* pnnS;
    CSList L;
    for(int i=0;i<uniqueCount;i++)
    {
        pnnS=new CSNode;
        pnnS->info=ct[i];
        pnnS->character[0]=Ltrs[i];
        pnnS->character[1]='\0';
        pnnS->pNext=NULL;
        pnnS->pDown=NULL;
        L.insert(pnnS);
    }

    int t,k;
    
    while(L.pHead->pNext!=NULL)
    {
        CSNode* pTemp1= L.remove();
        CSNode* pTemp2=L.remove();
        int sum = pTemp1->info + pTemp2->info;

        pnnS=new CSNode;
        pnnS->info=sum;
        for(t=0;pTemp1->character[t]!='\0';t++)
        {
            pnnS->character[t]=pTemp1->character[t];
        }
        for(k=0;pTemp2->character[k]!='\0';k++)
        {
            pnnS->character[t]=pTemp2->character[k];
            t++;
        }
        pnnS->character[t]='\0';
        pnnS->pNext=NULL;
        
        CTreeNode* pnt1= new CTreeNode;
        pnt1->info=sum;
        for(t=0;pTemp1->character[t]!='\0';t++)
        {
            pnt1->character[t]=pTemp1->character[t];
        }
        for(k=0;pTemp2->character[k]!='\0';k++)
        {
            pnt1->character[t]=pTemp2->character[k];
            t++;
        }
        pnt1->character[t]='\0';
        pnt1->pLeft=NULL;
        pnt1->pRight=NULL;

        //link the sorted list node to the tree node
        pnnS->pDown=pnt1;
        L.insert(pnnS);

        if(pTemp1->pDown==NULL)
        {
            CTreeNode* pnt2= new CTreeNode;
            pnt2->info=pTemp1->info;
            for(t=0;pTemp1->character[t]!='\0';t++)
            {
                pnt2->character[t]=pTemp1->character[t];
            }
            pnt2->character[t]='\0';
            pnt2->pLeft=NULL;
            pnt2->pRight=NULL;
            pnt1->pLeft=pnt2;
        }
        else
        {
            pnt1->pLeft=pTemp1->pDown;
        }
        if(pTemp2->pDown==NULL)
        {
            CTreeNode* pnt3= new CTreeNode;
            pnt3->info=pTemp2->info;
            for(t=0;pTemp1->character[t]!='\0';t++)
            {
                pnt3->character[t]=pTemp2->character[t];
            }
            pnt3->character[t]='\0';
            pnt3->pLeft=NULL;
            pnt3->pRight=NULL;
            pnt1->pRight=pnt3;
        }
        else
        {
            pnt1->pRight=pTemp2->pDown;
        }
        delete pTemp1;
        delete pTemp2;
    }
    CTreeNode* pT=L.pHead->pDown;
    char Bits[5000];  
    Bits[0] = '\0';   
    int len = 0;  
    traverseLeaves(pT, Bits, len); 

    CList List;
    Bits[0] = '\0';   
    len = 0;
    CNode* pTemp= makeClist(pT,Bits,len,List);
    /////////put huffman code in file
    CNode* pH=pTemp;
    while(pH!=NULL)
    {
        fl3.write(&pH->character,1);
        for(int t=0;pH->bits[t]!='\0';t++)
        {
            fl3.write(&pH->bits[t],1);
        }
        pH=pH->pnext;
    }
    fl.seekg(54, fl.beg);
    int ctBits=0;
    int i=0;
    int width = *(int *)&bmpHeader[18];
    int height = *(int *)&bmpHeader[22];
     for(i=0;i<width * height * 3;i++)
     {
        fl.read(&ch,1);
        char currentChar = ch;
        CNode* pTrav = pTemp;         
        while (pTrav != NULL) 
        {      
            if (currentChar == pTrav->character) 
            { 
                k = 0;
                while (pTrav->bits[k] != '\0') 
                {
                    ctBits++;
                    k++;
                }
                break; 
            }
            pTrav = pTrav->pnext; 
        }
        i++; 
    }
    cout<<"Bits Count: "<<ctBits<<endl;
    cout<<endl;

    //////////////////// ENCODE
    fl.seekg(54, fl.beg);
    int a = ctBits / 8; 
    if (ctBits % 8 != 0) 
    {
        a++; 
    }

    k = 0;    
    char currentBits[9];
    int charPos = 0;
    CNode* pBit = pTemp;
    CNode* pCatch=pTemp;
    int hh=0;
    for(int i=0;i<a;i++)
    {
        char x;
        x=0;
        char m;
        m=1;
        pBit = pCatch;
        int currentPos = 0;
        int bitCount = 0;
        fl.read(&ch,1);
        while (bitCount < 8 && hh++<h) 
        {
            if (pBit->character == ch) 
            {
                while (pBit->bits[charPos] != '\0' && bitCount < 8) 
                {
                    currentBits[currentPos] = pBit->bits[charPos];
                    currentPos++;
                    bitCount++;
                    charPos++;
                    if (bitCount == 8) 
                    {
                        currentBits[currentPos] = '\0';
                        break;
                    }
                }
                if (bitCount < 8 && pBit->bits[charPos] == '\0') 
                {
                    pBit = pTemp;
                    charPos=0;
                    k++;
                }
                if (bitCount == 8 && pBit->bits[charPos] == '\0') 
                {
                    k++;
                    charPos=0;
                    break;
                }
                if(bitCount==8 &&pBit->bits[charPos]!='\0')
                {
                    pCatch=pBit;
                    break;
                }
                if(bitCount<8 &&pBit->bits[charPos]!='\0')
                {
                    pCatch=pBit;
                    currentBits[currentPos] = '\0';
                }
            } 
            else 
            {
                pBit = pBit->pnext;
            }

            if (pBit == NULL) 
            {
                break;
            }
        }
        
        
        for(int b=0 ; currentBits[b]!='\0';b++)
        {
            if(currentBits[b]=='1')
            {
                x=(m<<7-b) | x;
            }
        }
        fl2.write(&x,1);     
    }


    return 0;
}
