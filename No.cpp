#include "No.h"

using namespace std;

No::No(){}

//construtor que joga um valor na vari�vel e pra o indexdor, ainda joga o next pra NULL
No::No(string nameP, int ind){

    nameValue = nameP;
    index = ind;
    next = NULL;

}

//retorna o pr�ximo n�
No* No::getNext(){

    return next;

}

//seta o next pra o pr�ximo n�
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

