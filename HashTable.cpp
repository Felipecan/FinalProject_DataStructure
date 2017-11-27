#include "HashTable.h"
#include "No.h"
#include <iostream>
#include <string>
#include <fstream>
#include <ctype.h>//para transfomrar M em m
#include <stdlib.h>
//#include<windows.h>//biblioteca para usar a função que ira dizer o tempo de execução dando em milissegundos
#include <time.h>//biblioteca para usar a função que ira dizer o tempo de execução dando em segundos

using namespace std;

//contrutor que seta o tamanho atual e a tabela para NULL
HashTable::HashTable(){

    int i = 0;
    tam = 0;
    while(i < tamHT){//setando a tabela para NULL que significa vazio

        hashT[i] = NULL;
        i++;

    }

}

void HashTable::deleteHashTable(){//método para deletar toda tabela Hash

    No *aux;

    for(int i = 0; i < tamHT; i++){//um for para todo array de ponteiros

        if(hashT[i] != NULL){//se algum ponteiro diferente de null

            while(hashT[i]->getNext() != NULL){//enquanto houver algo encadeado vai deletando

                aux = hashT[i];
                hashT[i]->setNext(aux->getNext());
                delete aux;

            }

            delete hashT[i];//deleta o primeiro nó encadeado no final

        }

    }

    delete[] hashT;//toda a tabela foi desalocada

}

int HashTable::computerStringToInt(string strName){//o método transforma uma string em algum valor inteiro e retorna esse valor

    int valueInt = 17;

    for(int i = 0; i < strName.length(); i++){

        valueInt = 31 * valueInt + ((int)strName[i]);

    }

    return valueInt;

}

int HashTable::computerHash(int xHash){//função Hash usando o método da divisão

    int valueHash =  ((xHash & 0x7FFFFFFF)%tamHT);
    return valueHash;

}

void HashTable::insertValue(string strInsert){//método para inserir algum valor na tabela

    int hashIndex = computerHash(computerStringToInt(strInsert));//computando o hash

    No *novo = new No(strInsert, hashIndex);//cria um nó novo para inserir em algum lugar

    if(hashT[hashIndex] == NULL){//se o lugar escolhido já estiver vago, o mesmo já aponta para o nó novo e incrementa no tamanho
                                    //e somente ele seta o last para algum
        hashT[hashIndex] = novo;
        tam++;

    }
    else{//caso esteja com algum nó ocupado, mas o mesmo hash, então encadeia

        novo->setNext(hashT[hashIndex]);
        hashT[hashIndex] = novo;
        tam++;

    }

}

int HashTable::searchValue(string strSearch){//método para procurar uma palavra na tabela hash

    int hashIndex;

    for(int i = 0; i < strSearch.length(); i++){//loop pra transformar uma palavra com letra maiúscula em todas minúscula

        strSearch[i] = tolower(strSearch[i]);

    }


    hashIndex = computerHash(computerStringToInt(strSearch));//computa o hash

    if(hashT[hashIndex] == NULL){

        //cout<<"Valor não encontrado, bucket vazio"<<endl;
        return 1;

    }

    if(hashT[hashIndex]->getNext() == NULL){//verifica se tem algum nó encadeado aqui

        if(hashT[hashIndex]->getNameValue() == strSearch){//se o nome no nó for igual ao que é procurado retorna 0 siginficando que o encontrou na tabela

            //cout<<"Valor encontrado: "<<hashT[hashIndex]->getNameValue()<<endl;
            return 0;

        }
        else{//caso não seja econtrado nada nesse bucket retonra 1

            //cout<<"Valor do hash e igual, mas o valor nao e correspondente"<<endl;
            return 1;

        }

    }
    else{//caso haja algo encadeado

        No *aux;
        aux = hashT[hashIndex];//aux recebe o primeiro no index

        while(aux->getNext() != NULL){//enquanto não chega ao último nó encadeado que apontará para null

            if(aux->getNameValue() == strSearch){//pergunta se o nome no nó é igual ao procurado, se for retorna 0 significando que é o mesmo

                //cout<<"Valor encontrado "<<aux->getNameValue()<<endl;
                return 0;

            }

            aux = aux->getNext();//caso não entre no if o aux recebe o próximo

        }

        if(aux->getNameValue() == strSearch){//apos chegar o ultimo não é possivel verificar o nome nele, aqui ele é verificado e segue a mesma lógica do 0 ou 1

            //cout<<"Valor encontrado "<<aux->getNameValue()<<endl;
            return 0;

        }
        else{

            //cout<<"Valor do hash e igual, mas o valor nao e correspondente"<<endl;
            return 1;

        }

    }

}

void HashTable::loadDict(){

    ifstream dictionary;//variável para manipular o txt
    string str;//auxiliar
    dictionary.open("ED.txt");//abre o dicionário

    while(!dictionary.eof()){//enquanto não for o final

        getline(dictionary, str);//pega um linha

        for(int i = 0; i<str.length(); i++){//loop pra transformar uma palavra com letra maiúscula em todas minúscula

            str[i] = tolower(str[i]);

        }

        insertValue(str);//chama o método insert para colocar o nome na tabela

    }

    dictionary.close();//fecha dicionário

}

void HashTable::readTxtOutsise(char* path){//método para leitura de arquivo externo e teste contra o dicionário

    ifstream txtFile, auxTxt; //uma variável para manipular o texto de teste e outra auxiliar
    ofstream result; //manipular o texto de saída
    string str, strAux, *auxString; //str serve para capturar toda linha, strAux pra pegar só uma palavra da linha e *auxString para criar um vetor dinâmico
    string::iterator it; //iterator auxiliar para percorrer toda linha filtrando espaços e caracteres invalidos, também serve para concatenar os caracteres
                        //da palavra que vai ser verificada
    int k = 0; //variável auxiliar
    int column = 0; //armazena a quantidade de coluna do texto
    int line = 0; //armazena a quantidade de linha do texto
    int numTWord = 0; //armazena a quantidade total de palavras do texto
    int erroPos = 0; //auxiliar para determinar o erro de caracteres invalidos no final da linha(dizer a coluna correta da ultima palavra)
    int numTWordErro = 0; //armazena a quantidade de palavras erradas
    double timeI = 0, timeF = 0, timeT = 0; //variáveis para determinar o tempo de execução



    txtFile.open(path); //abri arquivo de leitura

    if(!txtFile){//verificar se abriu corretamente o texto

        cout<<"Aquivo nao pode ser aberto\n";
        exit(-1);

    }

    result.open("Result.txt"); //abri arquivo de escrita

    //timeI = GetTickCount();//início da contagem de tempo da verificação em ms
    while(!txtFile.eof()){ //enquanto não for o fim do arquivo...

        getline(txtFile, str);//captura uma linha
        //cout<<str<<endl;

        for(it = str.begin(); it < str.end(); it++){//do início da string que é a linha capturada até o final...

            if(*it == ' '){//se o caractere for igual ao espaço(significa que leu toda uma palavra anteriormente)

                int aux = searchValue(strAux); //uma variável auxiliar vai armazenar se é 0 ou 1
                //int columnR = column - strAux.length(); //A coluna onde pode haver um erro é calculada aqui, tirando da coluna lida até agora o tamanho da string

                int verif = numTWord;//atribui a variável que conta o total de palavras pra testar no for abaixo
                for(int i = 0; i < strAux.length(); i++){

                    if(strAux[i] == '-'){//se for igual ao um hífen, então existe uma palavra antes

                        verif++; //aciciona um nas palavras totais(essa que vai ser atribuida abaixo)

                    }

                }

                verif++;//como o for anterior não adiciona na ultima palavra depois do hífen, adicionamos aqui

                if((verif-1) == numTWord){//agora se o verif-1(por causa da adicão aterior ser indevida) for igual ao número total
                                        // não existe palavra composta e adicionamos 1 no numTWord
                    numTWord++;

                }else{//caso não, atualizaremos  a contagem anterior

                    numTWord = verif;

                }

                //numTWord++; //aciciona um nas palavras totais
                erroPos = 0; //zera o caracteres invalidos

                if(aux == 0){//palavra encontrada, não faz nada

                    //cout<<"valor encontrado\n";
                    //cout<<"linha "<<line<<" coluna: "<<columnR<<endl;

                }
                else{

                    int columnR = column - strAux.length(); //A coluna onde pode haver um erro é calculada aqui, tirando da coluna lida até agora o tamanho da string
                    result<<line<<" - "<<columnR<<" : "<<strAux<<"\n";//escreve no texto a a linha, palavra e coluna errada
                    //cout<<line<<" - "<<columnR<<" : "<<strAux<<"\n";
                    numTWordErro++;//adiciona um no contador de erros

                }

                strAux.clear();//Limpa a string para uma próxima palavra

            }
            else{

                if(*it == ',' || *it == '.' || *it == ';' || *it == ':' || *it == '/"' || *it == '!' || *it == '?' || *it == '\\' || *it == '|' || *it == '@' || *it == '#' || *it == '$' || *it == '%' || *it == '¨' || *it == '&' || *it == '*' || *it == '(' || *it == ')' || *it == '_' || *it == '+' || *it == '=' || *it == '§' || *it == '[' || *it == ']' || *it == '{' || *it == '}' || *it == '/' || *it == '\n' || *it == '\0' || *it == '\t' || *it == '´' || *it == '`' || *it == '~' || *it == '^' || *it == 'ª' || *it == 'º' || *it == '§' || *it == '¬' || *it == '¢' || *it == '£' || *it == '³' || *it == '²' || *it == '¹'){//se o caractere tiver algum valor invalido não faz"nada"

                    erroPos++; //adiciona mais um pra um possivel erro final

                }
                else{

                    strAux = strAux + *it; // caso não seja nada das opaçoes assima, iremos concatenar até formar uma palavra completa(cheando ao espaço)

                }

            }

            column++;//adiciona mais um na coluna após tratar o caractere

        }

//ATEANÇÃO: NA ULTIMA PALAVRA DA LINHA ELE NÃO PODE ENTARR NO FOR, ENTÃO VERIFICAMOS LOGO APÓS, POR ESSE TRECHO ABAIXO;
            int aux = searchValue(strAux); //uma variável auxiliar vai armazenar se é 0 ou 1
            //int columnR = (column - erroPos) - strAux.length(); //A coluna onde pode haver um erro é calculada aqui, tirando da coluna lida até agora o tamanho da string e os caracteres invalidos no final

            int verif = numTWord;//atribui a variável que conta o total de palavras pra testar no for abaixo
            for(int i = 0; i < strAux.length(); i++){

                if(strAux[i] == '-'){//se for igual ao um hífen, então existe uma palavra antes

                    verif++; //aciciona um nas palavras totais(essa que vai ser atribuida abaixo)

                }

            }

            verif++;//como o for anterior não adiciona na ultima palavra depois do hífen, adicionamos aqui

            if((verif-1) == numTWord){//agora se o verif-1(por causa da adicão aterior ser indevida) for igual ao número total
                                        // não existe palavra composta e adicionamos 1 no numTWord
                numTWord++;

            }else{//caso não, atualizaremos  a contagem anterior

                numTWord = verif;

            }

            //numTWord++;
            erroPos = 0; //zera o caracteres invalidos

            if(aux == 0){//palavra encontrada, não faz nada

                //cout<<"valor encontrado\n";
                //cout<<"linha "<<line<<" coluna: "<<columnR<<endl;

            }
            else{

                int columnR = (column - erroPos) - strAux.length(); //A coluna onde pode haver um erro é calculada aqui, tirando da coluna lida até agora o tamanho da string e os caracteres invalidos no final
                result<<line<<" - "<<columnR<<" : "<<strAux<<"\n";//escreve no texto a a linha, palavra e coluna errada
                //cout<<line<<" - "<<columnR<<" : "<<strAux<<"\n";
                numTWordErro++;//adiciona um no contador de erros

            }

            strAux.clear();//limpa uma string para uma próxima palavra

        line++;//adiciona então uma linha
        column = 0;//zera a coluna pra uma próxima linha


    }
    //timeF = GetTickCount();//fim do tempo de execução em ms
    timeT = (timeF - timeI);//tempo final vai ser igual ao final menos o inicio em ms

    result.close();//fecha o arquivo de escrita

    auxTxt.open("Result.txt");//abri o arquivo que foi escrito logo antes como leitura
    auxString = new string[numTWordErro];//aloca um espaço do tamanho da quantida de palavras erradas

    while(k < numTWordErro){//loop ira pegar atrevés do getline todas as linhas com o texto da palvra errada escrito a pouco

        getline(auxTxt, auxString[k]);
        k++;

    }

    auxTxt.close(); // fecha o arquivo de leitra aberto a pouco

    result.open("Result.txt");//abri novamente o arquivo de agora como escrita
    result.clear();//limpa o txt para inserir corretamente as informações
    result<<"Numero total de palavras do texto: "<<numTWord<<"\n";//seta essas informações no arquivo
    result<<"Tempo de verificacao: "<<timeT<<" ms\n";//seta essas informações no arquivo
    result<<"Numero de palavras que falharam no spell check: "<<numTWordErro<<"\n";//seta essas informações no arquivo
    result<<"Lista de palavras que falharam no spell check: \n\n";//seta essas informações no arquivo
    result<<" Linha - Coluna : Palvra\n";//seta essas informações no arquivo
    result<<" ------------------------\n";//seta essas informações no arquivo

    k = 0;
    while(k < numTWordErro){//para inserir as palavras erradas capturadas agora a pouco, usamos o loop

        result<<" "<<auxString[k]<<"\n";
        k++;

    }

    result.close();//fecha o ultimo arquivo de escrita aberto
    txtFile.close();//fecha o arquivo testada de leitura

}


void HashTable::printAll(){

    int i = 0;
    int nulls = 0;
    int colisao = 0;
    int colisao2 = 0;
    while(i < tamHT){

         if(hashT[i] == NULL){

            std::cout<<"Hash["<<i<<"] vazio\n";
            nulls++;

         }
         else if(hashT[i]->getNext() != NULL){

            No *aux;
            aux = hashT[i];
            int au = 0;

            while(aux->getNext() != NULL){

                std::cout<<"Hash["<<i<<"] "<<aux->getNameValue()<<" ";
                aux = aux->getNext();
                colisao++;
                au++;



            }

            if(colisao2 > au){
                colisao2 = colisao2;
            }else{colisao2 = au;}


            cout<<"\n";

         }
         else{

            std::cout<<"Hash["<<i<<"] "<<hashT[i]->getNameValue()<<"\n";

         }


        i++;

    }

std::cout<<"Tamanho total = "<<tam<<" Quantidade de NULL's = "<<nulls<<" Quantidade de colisoes = "<<colisao<<" Maior numero de colisao = "<<colisao2<<endl;

}

int HashTable::getTam(){

    return tam;

}
