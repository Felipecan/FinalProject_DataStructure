#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "No.h"

using namespace std;

//tamanho da tabela hash
const int tamHT = 37253;//231571;//53197;75193//37253

class HashTable{

//declaração do tamanho em que a tabela está com os encadeamentos também, e um vetor de ponteiros para Nó
private:

    No *hashT[tamHT];
    int tam = 0;

//declaração dos métodos
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
