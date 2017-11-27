#include "No.h"

using namespace std;

No::No(){}

//construtor que joga um valor na variável e pra o indexdor, ainda joga o next pra NULL
No::No(string nameP, int ind){

    nameValue = nameP;
    index = ind;
    next = NULL;

}

//retorna o próximo nó
No* No::getNext(){

    return next;

}

//seta o next pra o próximo nó
void No::setNext(No *no){

    next = no;

}

//retorna o valor inserido
string No::getNameValue(){

    return nameValue;

}

//seta o valor inserido
void No::setNameValue(string strParam){

    nameValue = strParam;

}

//seta o valor do indexador
void No::setIndex(int ind){

    index = ind;

}

//retonra o valor do indexador inserido
int No::getIndex(){

    return index;

}

