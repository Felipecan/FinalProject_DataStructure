#ifndef NO_H
#define NO_H

#include <string>

using namespace std;

class No{

//declara��o do n� com seu valor e chave, servindo para encanear nas colis�es
private:
    string nameValue;
    int index;
    No *next;

//declara��es dos m�todos da classe
public:

    No();
    No(string nameP, int ind);
    No *getNext();
    void setNext(No *no);
    string getNameValue();
    void setNameValue(string strParam);
    void setIndex(int ind);
    int getIndex();

};

#endif // NO_H
