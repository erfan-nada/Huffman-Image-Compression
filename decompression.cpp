#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class CNode {
public:
    char character;
    char bits[100];
    CNode *pnext;
};

class CList {
public:
    CNode *pHead;
    CNode *pTail;

    CList() {
        pHead = NULL;
        pTail = NULL;
    }

    ~CList() {
        CNode *pTrav = pHead;
        while (pHead != NULL) {
            pHead = pTrav->pnext;
            pTrav->pnext = NULL;
            delete pTrav;
            pTrav = pHead;
        }
    }

    void Attach(CNode *pnn) {
        if (pHead == NULL) {
            pHead = pnn;
            pTail = pnn;
        } else {
            pTail->pnext = pnn;
            pTail = pnn;
        }
    }
};

int compareStrings(char *str1, char *str2)
{
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0')
    {
        if (str1[i] != str2[i])
        {
            return 0;
        }
        i++;
    }
    if (str1[i] == '\0' && str2[i] == '\0')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int main() 
{
    ifstream fl("C:\\Users\\erfan\\Desktop\\Huffman Tree-Project\\encoded.bmp", ifstream::binary);
    ifstream f3("C:\\Users\\erfan\\Desktop\\Huffman Tree-Project\\Huffman_Code.bmp", ifstream::binary);
    ofstream fl2("C:\\Users\\erfan\\Desktop\\Huffman Tree-Project\\Decompressed.bmp", ofstream::binary);

    char bmpHeader[54];
    fl.read(bmpHeader, 54);
    fl2.write(bmpHeader, 54);

    // Read Huffman codes
    f3.seekg(0, f3.end);
    int c = f3.tellg();
    f3.seekg(0, f3.beg);
    char *huffmanArray = new char[c];
    f3.read(huffmanArray, c);

    // Build Huffman code list
    CNode *pnn;
    CList L;
    for (int t = 0; t < c; t++) {
        if (huffmanArray[t] != '0' && huffmanArray[t] != '1') {
            pnn = new CNode;
            pnn->character = huffmanArray[t];
            int bitIndex = 0;
            t++;
            while (t < c && (huffmanArray[t] == '0' || huffmanArray[t] == '1')) {
                pnn->bits[bitIndex++] = huffmanArray[t];
                t++;
            }
            pnn->bits[bitIndex] = '\0';
            pnn->pnext = NULL;
            L.Attach(pnn);
            t--;
        }
    }

    fl.seekg(54, fl.beg);

    char decodeBits[100];
    int bitIndex = 0;
    char ch;
    int width = *reinterpret_cast<int *>(&bmpHeader[18]);
    int height = *reinterpret_cast<int *>(&bmpHeader[22]);
    int rowSize = (width * 3 + 3) & ~3;
    char *rowBuffer = new char[rowSize];

    for (int y = 0; y < height; y++) 
    {
        int pixelIndex = 0;
        for (int x = 0; x < rowSize; x++) 
        {
            if (x < width * 3) 
            {
                if (bitIndex == 0) 
                {
                    fl.read(&ch, 1);
                }

                char m = 1;
                for (int j = 7; j >= 0; j--) 
                {
                    if ((ch & (m << j)) > 0) 
                    {
                        decodeBits[bitIndex++] = '1';
                    } 
                    else 
                    {
                        decodeBits[bitIndex++] = '0';
                    }
                    decodeBits[bitIndex] = '\0';

                    CNode *pTrav = L.pHead;
                    while (pTrav != NULL) 
                    {
                        if (compareStrings(decodeBits, pTrav->bits)) 
                        {
                            rowBuffer[pixelIndex++] = pTrav->character;
                            bitIndex = 0;
                            break;
                        }
                        pTrav = pTrav->pnext;
                    }
                }
            } 
            else 
            {
                rowBuffer[x] = 0;
            }
        }

        if (pixelIndex < rowSize) {
            while (pixelIndex < rowSize) 
            {
                rowBuffer[pixelIndex++] = 0; // Padding 
            }
        }

        fl2.write(rowBuffer, rowSize);
    }

    delete[] rowBuffer;
    delete[] huffmanArray;
    fl.close();
    f3.close();
    fl2.close();

    return 0;
}



