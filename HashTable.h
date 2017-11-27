#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "No.h"

using namespace std;

//tamanho da tabela hash
const int tamHT = 37253;//231571;//53197;75193//37253

class HashTable{

//declara��o do tamanho em que a tabela est� com os encadeamentos tamb�m, e um vetor de ponteiros para N�
private:

    No *hashT[tamHT];
    int tam = 0;

//declara��o dos m�todos
public:

    HashTable();
    int computerStringToInt(string strName);
    int computerHash(int x);
    void insertValue(string strInsert);
    int searchValue(string strSearch);
    void deleteHashTable();
    void loadDict();
    void readTxtOutsise(char* way);
    void printAll();
    int getTam();

};
#endif // HASHTABLE_H
