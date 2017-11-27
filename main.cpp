#include <iostream>
#include <fstream>
#include <ctype.h>
#include "HashTable.h"
#include "No.h"
#include <cstring>
#include <stdlib.h>

using namespace std;

int main(){

HashTable hash_1;
hash_1.loadDict();
//hash_1.printAll();
char w[50];

cout<<"digite o caminho ";
scanf("%s", &w);
hash_1.readTxtOutsise(&w[0]);

//system("pause");
return 0;

}
